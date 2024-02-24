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
        shutil.rmtree(THIRD_PARTY_DIR)


def init(force=False):
    print("Initializing development environment")
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
    args = parser.parse_args()
    if args.command == "init":
        init(args.force)
    elif args.command == "clean":
        clean()
    else:
        parser.print_help()


if __name__ == "__main__":
    main()
