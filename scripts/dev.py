import argparse
import shutil
import os
import subprocess
from contextlib import contextmanager


@contextmanager
def push_dir(target_dir):
    current_dir = os.getcwd()
    try:
        os.chdir(target_dir)
        yield
    finally:
        os.chdir(current_dir)


THIRD_PARTY_DIR = "third_party"
CPYTHON_BRANCH = "target"


def clean():
    print("Cleaning development environment")
    if os.path.exists(THIRD_PARTY_DIR):
        print("Removing third party directory")
        shutil.rmtree(THIRD_PARTY_DIR)
    print("Cleaning rust project")
    subprocess.check_call(["cargo", "clean"])


def init(force=False):
    print("Initializing development environment")
    print("Installing rust nightly")
    subprocess.check_call(["rustup", "install", "nightly"])
    subprocess.check_call(
        ["rustup", "component", "add", "rustfmt", "clippy", "--toolchain", "nightly"]
    )
    subprocess.check_call(["rustup", "override", "set", "nightly"])

    if os.path.exists(THIRD_PARTY_DIR):
        if force:
            print("Forcing initialization")
            clean()
        else:
            print("Development environment already initialized")
            return

    os.makedirs(THIRD_PARTY_DIR, exist_ok=True)
    with push_dir(THIRD_PARTY_DIR):
        subprocess.check_call(
            [
                "git",
                "clone",
                "--depth=1",
                f"--branch={CPYTHON_BRANCH}",
                "https://github.com/oneofthezombies/cpython.git",
            ]
        )
        with push_dir("cpython"):
            os.makedirs("debug", exist_ok=True)
            with push_dir("debug"):
                subprocess.check_call(["../configure", "--with-pydebug"])
                subprocess.check_call(["make", "-j"])


def check():
    subprocess.check_call(
        ["cargo", "check", "--workspace", "--all-targets", "--all-features"]
    )
    subprocess.check_call(
        [
            "cargo",
            "clippy",
            "--workspace",
            "--all-targets",
            "--all-features",
            "--",
            "-D",
            "clippy::all",
            "-D",
            "clippy::pedantic",
        ]
    )
    subprocess.check_call(["cargo", "fmt", "--all", "--check"])


def test():
    subprocess.check_call(
        [
            "cargo",
            "test",
            "--workspace",
            "--all-targets",
            "--all-features",
            "--",
            "--nocapture",
        ]
    )


def pre_push():
    check()
    test()


def main():
    parser = argparse.ArgumentParser(description="Development utilities")
    command_parser = parser.add_subparsers(dest="command", help="Available commands")
    init_parser = command_parser.add_parser(
        "init", help="Initialize development environment"
    )
    init_parser.add_argument(
        "--force", action="store_true", help="Force initialization"
    )
    clean_parser = command_parser.add_parser(
        "clean", help="Clean development environment"
    )
    check_parser = command_parser.add_parser(
        "check", help="Run check, clippy and rustfmt"
    )
    test_parser = command_parser.add_parser("test", help="Run tests")
    pre_push_parser = command_parser.add_parser(
        "pre-push", help="Run pre-push checks and tests"
    )
    args = parser.parse_args()
    if args.command == "init":
        init(args.force)
    elif args.command == "clean":
        clean()
    elif args.command == "check":
        check()
    elif args.command == "test":
        test()
    else:
        parser.print_help()


if __name__ == "__main__":
    main()
