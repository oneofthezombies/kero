import argparse
import os
import shutil
import subprocess

from common import BUILD_DIR, THIRD_PARTY_DIR
from doctor import doctor


def clean(all: bool):
    if os.path.exists(BUILD_DIR):
        print(f"Deleting {BUILD_DIR}")
        shutil.rmtree(BUILD_DIR)

    if all:
        if os.path.exists(THIRD_PARTY_DIR):
            print(f"Deleting {THIRD_PARTY_DIR}")
            shutil.rmtree(THIRD_PARTY_DIR)


def build():
    subprocess.check_call(
        [
            "cmake",
            "-G",
            "Ninja",
            "-S",
            "src",
            "-B",
            BUILD_DIR,
        ]
    )
    subprocess.check_call(["ninja"], cwd=BUILD_DIR)


def cli():
    parser = argparse.ArgumentParser(description="Kero Development Tool.")
    commands = parser.add_subparsers(dest="command")
    clean_parser = commands.add_parser(
        "clean", help="Clean the Kero development environment."
    )
    clean_parser.add_argument(
        "--all",
        action="store_true",
        help="Also clean the third_party directory.",
    )
    _doctor_parser = commands.add_parser(
        "doctor", help="Check the Kero development environment."
    )
    _build_parser = commands.add_parser("build", help="Build the Kero.")
    args = parser.parse_args()
    if args.command == "clean":
        clean(args.all)
    elif args.command == "doctor":
        doctor()
    elif args.command == "build":
        build()
    else:
        parser.print_help()


if __name__ == "__main__":
    cli()