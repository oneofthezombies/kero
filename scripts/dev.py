import argparse
import os
import re
import shutil
import subprocess
from typing import TypedDict

THIRD_PARTY_DIR = "third_party"


def clean():
    if os.path.exists(THIRD_PARTY_DIR):
        print(f"Deleting {THIRD_PARTY_DIR}")
        shutil.rmtree(THIRD_PARTY_DIR)


def doctor():
    class CheckResult(TypedDict):
        ok: bool
        commands: list[str]
        output: str
        error: str

    def python() -> CheckResult:
        commands = ["python", "--version"]
        output = subprocess.check_output(commands, encoding="utf-8").strip()
        match = re.match(
            r"Python (?P<major>\d+)\.(?P<minor>\d+)\.(?P<patch>\d+)", output
        )
        if match is None:
            return {
                "ok": False,
                "commands": commands,
                "output": output,
                "error": f"Python version not found in output: {output}",
            }
        major = int(match.group("major"))
        minor = int(match.group("minor"))
        patch = int(match.group("patch"))
        if major < 3 or (major == 3 and minor < 12):
            return {
                "ok": False,
                "commands": commands,
                "output": output,
                "error": f"Python version {major}.{minor}.{patch} is not supported. Please use Python 3.12 or later.",
            }
        return {"ok": True, "commands": commands, "output": output, "error": ""}

    results = [python()]
    ok = True
    print("-" * 80)
    for result in results:
        print(f"Command: {' '.join(result['commands'])}")
        print(f"Output: {result['output']}")
        if result["ok"]:
            print(f"OK")
        else:
            ok = False
            print(f"Error: {result['error']}")
        print("-" * 80)
    if not ok:
        exit(1)


def main():
    parser = argparse.ArgumentParser(description="Kero Development Tool.")
    commands = parser.add_subparsers(dest="command")
    _clean_parser = commands.add_parser(
        "clean", help="Clean the Kero development environment."
    )
    _doctor_parser = commands.add_parser(
        "doctor", help="Check the Kero development environment."
    )
    args = parser.parse_args()
    if args.command == "clean":
        clean()
    elif args.command == "doctor":
        doctor()
    else:
        parser.print_help()


if __name__ == "__main__":
    main()
