import { spawnSync } from "child_process";

function run(command, args, options) {
  console.log(
    `Running ${command} ${args.join(" ")} on ${options.cwd || process.cwd()}`
  );
  const result = spawnSync(command, args, options);
  if (result.status !== 0) {
    process.exit(result.status);
  }
  console.log(`Done running ${command} ${args.join(" ")}`);
}

function checkCommand(command) {
  console.log(`Checking ${command}...`);
  run("which", [command], { stdio: "inherit" });
  console.log(`Found ${command}`);
}

function installTreeSitterCli() {
  run("cargo", ["install", "tree-sitter-cli", "--version", "0.22.4"], {
    stdio: "inherit",
  });
}

function installTreeSitterKero() {
  run("npm", ["install", "--ignore-scripts"], {
    stdio: "inherit",
    cwd: "src/tree-sitter-kero",
  });
}

function generateTreeSitterKero() {
  run("tree-sitter", ["generate", "--no-bindings"], {
    stdio: "inherit",
    cwd: "src/tree-sitter-kero",
  });

  testTreeSitterKero();
}

function testTreeSitterKero() {
  run("tree-sitter", ["test"], {
    stdio: "inherit",
    cwd: "src/tree-sitter-kero",
  });
}

function generateCompileCommands() {
  run("bazel", ["run", "@hedron_compile_commands//:refresh_all"], {
    stdio: "inherit",
  });
}

function help() {
  console.log("Usage: dev.mjs [command]");
  console.log("Commands:");
  // prettier-ignore
  console.log("  kero init: Install Tree-sitter CLI and install Tree-sitter Kero npm package");
  console.log("  kero gen: Generate Tree-sitter parser for Kero and run tests");
  console.log("  ide: Generate IDE support files");
  process.exit(1);
}

function main() {
  const args = process.argv.slice(2);
  const command = args[0] || "help";
  const subcommand = args[1] || "";
  if (command === "kero") {
    if (subcommand === "init") {
      checkCommand("cargo");
      installTreeSitterCli();
      checkCommand("npm");
      installTreeSitterKero();
    } else if (subcommand === "gen") {
      generateTreeSitterKero();
    } else {
      help();
    }
  } else if (command === "ide") {
    generateCompileCommands();
  } else {
    help();
  }
}

main();
