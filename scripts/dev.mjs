import { Command } from "commander";
import { spawn } from "child_process";
import fs from "fs";

const THIRD_PARTY_DIR = "third_party";
const NODE_BRANCH = "target";
const CPYTHON_BRANCH = "target";

async function run(command, args, options = {}) {
  return new Promise((resolve, reject) => {
    const child = spawn(command, args, {
      stdio: "inherit",
      ...options,
    });
    child.on("exit", (code, signal) => {
      if (code === 0) {
        resolve();
      } else {
        reject(
          new Error(`Command failed with code ${code} and signal ${signal}`)
        );
      }
    });
  });
}

async function clean() {
  async function cleanThirdParty() {
    const stat = await fs.promises.stat(THIRD_PARTY_DIR).catch(() => null);
    if (stat) {
      await fs.promises.rm(THIRD_PARTY_DIR, { recursive: true });
    }
  }

  async function cleanRust() {
    await run("cargo", ["clean"]);
  }

  await cleanThirdParty();
  await cleanRust();
}

async function init() {
  async function initRust() {
    await run("rustup", ["install", "nightly"]);
    await run("rustup", [
      "component",
      "add",
      "rustfmt",
      "clippy",
      "--toolchain",
      "nightly",
    ]);
    await run("rustup", ["override", "set", "nightly"]);
  }

  async function initThirdParty() {
    const stat = await fs.promises.stat(THIRD_PARTY_DIR).catch(() => null);
    if (stat) {
      console.log(`${THIRD_PARTY_DIR} directory already exists, skipped.`);
      return;
    }

    await fs.promises.mkdir(THIRD_PARTY_DIR, { recursive: true });
    process.chdir(THIRD_PARTY_DIR);
    await run("git", [
      "clone",
      "--depth=1",
      `--branch=${NODE_BRANCH}`,
      "https://github.com/oneofthezombies/node.git",
    ]);
    await run("git", [
      "clone",
      "--depth=1",
      `--branch=${CPYTHON_BRANCH}`,
      "https://github.com/oneofthezombies/cpython.git",
    ]);
    process.chdir("cpython");
    const env = {
      ...process.env,
    };
    if (process.platform === "darwin") {
      env.CFLAGS = `-I${process.env.HOMEBREW_PREFIX}/include`;
      env.LDFLAGS = `-L${process.env.HOMEBREW_PREFIX}/lib`;
    }
    await run("./configure", ["--with-pydebug"], {
      env,
    });
    await run("make", ["-j"]);
  }

  await initRust();
  await initThirdParty();
}

async function check() {
  await run("cargo", [
    "check",
    "--workspace",
    "--all-targets",
    "--all-features",
  ]);
  await run(
    "cargo",
    [
      "clippy",
      "--workspace",
      "--all-targets",
      "--all-features",
      "--",
      "-D",
      "clippy::all",
      "-D",
      "clippy::pedantic",
    ],
    { env: { ...process.env, RUSTFLAGS: "-Z macro-backtrace" } }
  );
  await run("cargo", ["fmt", "--all", "--check"]);
}

async function test() {
  await run("cargo", [
    "test",
    "--workspace",
    "--all-targets",
    "--all-features",
    "--",
    "--nocapture",
  ]);
}

async function main() {
  const program = new Command();
  program
    .name("dev") //
    .description("Development utilities");

  program
    .command("clean") //
    .description("Clean the development environment")
    .action(clean);

  program
    .command("init") //
    .description("Initialize the development environment")
    .action(init);

  program
    .command("check") //
    .description("Run check, clippy and rustfmt")
    .action(check);

  program
    .command("test") //
    .description("Run tests")
    .action(test);

  program.parse();
}

await main();
