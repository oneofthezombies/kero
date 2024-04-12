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
  const result = spawnSync("npm", ["install"], {
    stdio: "inherit",
    cwd: "third_party/tree-sitter-kero",
  });

  if (result.error) {
    console.error(result.error);
    process.exit(1);
  }
}

function main() {
  installTreeSitterCli();
  installTreeSitterKero();
}

main();
