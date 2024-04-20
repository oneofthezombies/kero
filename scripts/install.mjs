import { spawnSync } from "child_process";
import os from "os";
import fs from "fs";
import path from "path";

function runCommand(command, args, options) {
  console.log(
    `Running ${command} ${args.join(" ")} on ${options?.cwd || process.cwd()}`
  );
  const result = spawnSync(command, args, options);
  if (result.status !== 0) {
    process.exit(result.status);
  }
  console.log(`Done running ${command} ${args.join(" ")}`);
}

function checkCommand(command) {
  console.log(`Checking ${command}...`);
  if (command.indexOf("/") === -1) {
    runCommand("which", [command], { stdio: "inherit" });
  } else {
    if (!fs.existsSync(command)) {
      console.error(`Command ${command} not found`);
      process.exit(1);
    }
  }
  console.log(`Found ${command}`);
}

function run(command, args, options) {
  checkCommand(command);
  runCommand(command, args, options);
}

const args = process.argv.slice(2);

const buildSystem = (() => {
  const buildSystemArg = args.find((arg) => arg.startsWith("--build-system"));
  const buildSystem = buildSystemArg ? buildSystemArg.split("=")[1] : "ninja";
  if (buildSystem !== "ninja" && buildSystem !== "make") {
    console.error(`Invalid build system ${buildSystem}`);
    process.exit(1);
  }
  return buildSystem;
})();

const archivesPath = path.resolve(os.homedir(), "archives");
run("mkdir", ["-p", archivesPath]);
process.chdir(archivesPath);

const localPath = path.resolve(os.homedir(), ".local");
run("mkdir", ["-p", localPath]);

const COMMON_CMAKE_ARGS = [
  "-G",
  buildSystem === "ninja" ? "Ninja" : "Unix Makefiles",
  `-DCMAKE_INSTALL_PREFIX=${localPath}`,
  "-DCMAKE_BUILD_TYPE=Debug",
  "-DCMAKE_C_COMPILER=clang",
  "-DCMAKE_CXX_COMPILER=clang++",
  "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON",
];

const getDefaultBuildPath = (project) =>
  path.resolve(archivesPath, project, "build");

const defaultBuild = () => {
  if (buildSystem === "ninja") {
    run("cmake", ["--build", "."], { stdio: "inherit" });
  } else if (buildSystem === "make") {
    run("make", ["-j"], { stdio: "inherit" });
  }
};

const defaultInstall = () => {
  run("sudo", ["cmake", "--install", "."], { stdio: "inherit" });
};

const defaultCopyCompileCommands = (project) => {
  const compileCommandsPath = path.resolve(
    localPath,
    "share",
    "compile_commands",
    project
  );
  run("mkdir", ["-p", compileCommandsPath], { stdio: "inherit" });
  run(
    "cp",
    [
      "-f",
      "compile_commands.json",
      path.resolve(compileCommandsPath, "compile_commands.json"),
    ],
    { stdio: "inherit" }
  );
};

const dependencyFactories = [
  () => {
    const version = "18.1.4";
    const project = `llvm-project-llvmorg-${version}`;
    return {
      project,
      download: () => {
        run(
          "curl",
          [
            "-LO",
            `https://github.com/llvm/llvm-project/archive/refs/tags/llvmorg-${version}.zip`,
          ],
          { stdio: "inherit" }
        );
        run("unzip", [`llvmorg-${version}.zip`], { stdio: "inherit" });
        run("rm", ["-f", `llvmorg-${version}.zip`], { stdio: "inherit" });
      },
      configure: () => {
        run(
          "cmake",
          [
            "../llvm",
            ...COMMON_CMAKE_ARGS,
            "-DLLVM_ENABLE_PROJECTS=clang;lld;lldb",
            "-DLLVM_ENABLE_ASSERTIONS=ON",
            "-DLLVM_USE_LINKER=lld",
            "-DLLDB_INCLUDE_TESTS=OFF",
          ],
          { stdio: "inherit" }
        );
      },
    };
  },
  () => {
    const version = "0.2.4";
    const project = `cpp-tree-sitter-${version}`;
    return {
      project,
      download: () => {
        run(
          "curl",
          [
            "-LO",
            `https://github.com/oneofthezombies/cpp-tree-sitter/archive/refs/tags/v${version}.zip`,
          ],
          { stdio: "inherit" }
        );
        run("unzip", [`v${version}.zip`], { stdio: "inherit" });
        run("rm", ["-f", `v${version}.zip`], { stdio: "inherit" });
      },
      configure: () => {
        run("cmake", ["..", ...COMMON_CMAKE_ARGS], { stdio: "inherit" });
      },
    };
  },
  () => {
    const version = "1.14.0";
    const project = `googletest-${version}`;
    return {
      project,
      download: () => {
        run(
          "curl",
          [
            "-LO",
            `https://github.com/google/googletest/archive/refs/tags/v${version}.zip`,
          ],
          { stdio: "inherit" }
        );
        run("unzip", [`v${version}.zip`], { stdio: "inherit" });
        run("rm", ["-f", `v${version}.zip`], { stdio: "inherit" });
      },
      configure: () => {
        run("cmake", ["..", ...COMMON_CMAKE_ARGS], { stdio: "inherit" });
      },
    };
  },
];

for (const factory of dependencyFactories) {
  const {
    project,
    download,
    configure,
    buildPath,
    build,
    install,
    copyCompileCommands,
  } = factory();
  const projectPath = path.resolve(archivesPath, project);
  const cwd = process.cwd();
  try {
    if (!fs.existsSync(projectPath)) {
      download();
    }

    const resolvedBuildPath = buildPath || getDefaultBuildPath(project);
    run("mkdir", ["-p", resolvedBuildPath]);
    process.chdir(resolvedBuildPath);

    configure();

    if (build) {
      build();
    } else {
      defaultBuild();
    }

    if (install) {
      install();
    } else {
      defaultInstall();
    }

    if (copyCompileCommands) {
      copyCompileCommands();
    } else {
      defaultCopyCompileCommands(project);
    }
  } catch (e) {
    console.error(e);
    process.exit(1);
  } finally {
    process.chdir(cwd);
  }
}
