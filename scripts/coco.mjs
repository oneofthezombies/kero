/**
 * compile_commands.json supporting source code management script
 */

import { spawnSync } from "child_process";
import os from "os";
import fs from "fs";
import path from "path";

process.on("unhandledRejection", (reason) => {
  console.error(`Unhandled Rejection: ${reason}`);
  process.exit(1);
});

process.on("uncaughtException", (error) => {
  console.error(`Uncaught Exception: ${error}`);
  process.exit(1);
});

const CACHE_PATH = path.resolve(process.cwd(), ".cache");
const TEMP_PATH = path.resolve(process.cwd(), ".temp");
const LOCAL_PATH = path.resolve(process.cwd(), ".local");
const COMMON_CMAKE_ARGS = [
  "-G Ninja",
  `-DCMAKE_INSTALL_PREFIX=${LOCAL_PATH}`,
  "-DCMAKE_BUILD_TYPE=Debug",
  "-DCMAKE_C_COMPILER=clang",
  "-DCMAKE_CXX_COMPILER=clang++",
  "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON",
];

function main() {
  const args = process.argv.slice(2);
  const command = args[0] || "";

  run("mkdir", ["-p", CACHE_PATH]);
  run("mkdir", ["-p", TEMP_PATH]);
  run("mkdir", ["-p", LOCAL_PATH]);

  if (command === "install") {
    install();
  } else if (command === "build") {
    build();
  } else {
    help();
  }
}

main();

// #region Functions

function help() {
  console.log("Usage: node scripts/coco.mjs <command> [options]");
  console.log("Commands:");
  console.log("  install");
  console.log("  build");
  process.exit(1);
}

function install() {
  cacheCppTreeSitter();
  // cacheGoogletest();
  // cacheLlvm();
}

function build() {}

function cacheLlvm() {
  downloadGithubZip({
    project: "llvm",
    url: "https://github.com/llvm/llvm-project/archive/refs/tags/llvmorg-18.1.4.zip",
    unzippedDir: "llvm-project-llvmorg-18.1.4",
  });
  withPath(getProjectPath("llvm"), () => {
    run("cmake", [
      "-S",
      "llvm",
      "-B",
      "build",
      ...COMMON_CMAKE_ARGS,
      "-DLLVM_ENABLE_PROJECTS=",
      "-DLLVM_ENABLE_ASSERTIONS=ON",
      "-DLLVM_USE_LINKER=lld",
      "-DLLDB_INCLUDE_TESTS=OFF",
    ]);
    run("cmake", ["--build", "build"]);
    run("sudo", ["cmake", "--install", "build"]);
  });
}

function cacheCppTreeSitter() {
  const projectPath = getProjectPath("cpp-tree-sitter");
  downloadGithubZip({
    project: "cpp-tree-sitter",
    projectPath,
    url: "https://github.com/oneofthezombies/cpp-tree-sitter/archive/refs/tags/v0.2.4.zip",
    unzippedDir: "cpp-tree-sitter-0.2.4",
  });
  withPath(projectPath, () => {
    run("cmake", ["-S", ".", "-B", "build", ...COMMON_CMAKE_ARGS]);
    run("sudo", ["cmake", "--install", "build"]);
  });
}

function cacheGoogletest() {
  const projectPath = getProjectPath("googletest");
  downloadGithubZip({
    project: "googletest",
    projectPath,
    url: "https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip",
    unzippedDir: "googletest-1.14.0",
  });
  withPath(projectPath, () => {
    run("cmake", ["-S", ".", "-B", "build", ...COMMON_CMAKE_ARGS]);
    run("sudo", ["cmake", "--install", "build"]);
  });
}

function runCommand(command, args, options) {
  console.log(
    `Running ${command} ${args.join(" ")} on ${options?.cwd || process.cwd()}`
  );
  options = options || {};
  options.stdio = options.stdio || "inherit";
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

function downloadGithubZip(options) {
  const { project, projectPath, url, unzippedDir } = options;
  try {
    if (fs.existsSync(TEMP_PATH)) {
      run("rm", ["-rf", TEMP_PATH]);
    }
    run("mkdir", ["-p", TEMP_PATH]);

    const metadataPath = path.resolve(CACHE_PATH, `${project}.json`);
    const metadata = fs.existsSync(metadataPath)
      ? JSON.parse(fs.readFileSync(metadataPath, "utf8"))
      : {};

    if (metadata.url === url) {
      console.log(`Already cached ${project}`);
      return;
    }

    const zipPath = path.resolve(TEMP_PATH, `${project}.zip`);
    run("curl", ["-L", "-o", zipPath, url]);
    run("unzip", [zipPath]);
    run("rm", ["-f", zipPath]);

    const unzippedPath = path.resolve(TEMP_PATH, unzippedDir);
    if (!fs.existsSync(unzippedPath)) {
      console.error(`Unzipped path ${unzippedPath} not found`);
      process.exit(1);
    }

    if (fs.existsSync(projectPath)) {
      run("rm", ["-rf", projectPath]);
    }

    run("mv", [unzippedPath, projectPath]);

    metadata.url = url;
    fs.writeFileSync(metadataPath, JSON.stringify(metadata));
  } finally {
    run("rm", ["-rf", TEMP_PATH]);
  }
}

function getProjectPath(project) {
  return path.resolve(CACHE_PATH, project);
}

function withPath(path, fn) {
  const cwd = process.cwd();
  try {
    process.chdir(path);
    fn();
  } finally {
    process.chdir(cwd);
  }
}

// #endregion
