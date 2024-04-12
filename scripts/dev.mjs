import { spawnSync } from "child_process";

function installTreeSitterCli() {
  const result = spawnSync("cargo", ["install", "tree-sitter-cli"], {
    stdio: "inherit",
  });

  if (result.error) {
    console.error(result.error);
    process.exit(1);
  }
}

function installTreeSitterKero() {
  const result = spawnSync("npm", ["install", "--ignore-scripts"], {
    stdio: "inherit",
    cwd: "third_party/tree-sitter-kero",
  });

  if (result.error) {
    console.error(result.error);
    process.exit(1);
  }
}

function install() {
  installTreeSitterCli();
  installTreeSitterKero();
}

function generateTreeSitterKero() {
  const result = spawnSync("tree-sitter", ["generate", "--no-bindings"], {
    stdio: "inherit",
    cwd: "third_party/tree-sitter-kero",
  });

  if (result.error) {
    console.error(result.error);
    process.exit(1);
  }
}

function generate() {
  generateTreeSitterKero();
}

function parse() {
  const result = spawnSync("tree-sitter", ["parse"], {
    stdio: "inherit",
    cwd: "third_party/tree-sitter-kero",
  });

  if (result.error) {
    console.error(result.error);
    process.exit(1);
  }
}

function help() {
  console.log("Usage: dev.mjs [command]");
  console.log("Commands:");
  console.log("  install: Install dependencies");
  console.log("  generate: Generate parser");
  console.log("  parse: Parse source file");
}

function main() {
  const args = process.argv.slice(2);
  const command = args[0] || "help";
  if (command === "install") {
    install();
  } else if (command === "generate") {
    generate();
  } else if (command === "parse") {
    parse();
  } else {
    help();
  }
}

main();
