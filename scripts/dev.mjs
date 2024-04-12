import { spawnSync } from "child_process";

function run(command, args, options) {
  const result = spawnSync(command, args, options);
  if (result.error) {
    console.error(result.error);
    process.exit(1);
  }
}

function installTreeSitterCli() {
  run("cargo", ["install", "tree-sitter-cli"], {
    stdio: "inherit",
  });
}

function installTreeSitterKero() {
  run("npm", ["install", "--ignore-scripts"], {
    stdio: "inherit",
    cwd: "third_party/tree-sitter-kero",
  });
}

function install() {
  installTreeSitterCli();
  installTreeSitterKero();
}

function generateTreeSitterKero() {
  run("tree-sitter", ["generate", "--no-bindings"], {
    stdio: "inherit",
    cwd: "third_party/tree-sitter-kero",
  });
}

function generateCompileCommands() {
  run("bazel", ["build", "@hedron_compile_commands//:all"], {
    stdio: "inherit",
  });
}

function generate() {
  generateTreeSitterKero();
  generateCompileCommands();
}

function help() {
  console.log("Usage: dev.mjs [command]");
  console.log("Commands:");
  console.log("  install: Install dependencies");
  console.log("  generate: Generate parser");
  process.exit(1);
}

function main() {
  const args = process.argv.slice(2);
  const command = args[0] || "help";
  if (command === "install") {
    install();
  } else if (command === "generate") {
    generate();
  } else {
    help();
  }
}

main();
