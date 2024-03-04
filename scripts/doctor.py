import re
import subprocess
from typing import TypedDict


class CheckResult(TypedDict):
    ok: bool
    commands: list[str]
    stdout: str
    stderr: str
    error: str


def _python() -> CheckResult:
    comp = subprocess.run(
        ["python", "--version"],
        capture_output=True,
        universal_newlines=True,
        encoding="utf-8",
    )
    if comp.returncode != 0:
        return {
            "ok": False,
            "commands": comp.args,
            "stdout": comp.stdout,
            "stderr": comp.stderr,
            "error": f"Python version command failed with return code {comp.returncode}",
        }
    output = comp.stdout.strip()
    match = re.match(r"Python (?P<major>\d+)\.(?P<minor>\d+)\.(?P<patch>\d+)", output)
    if match is None:
        return {
            "ok": False,
            "commands": comp.args,
            "stdout": comp.stdout,
            "stderr": comp.stderr,
            "error": f"Python version not found in output: {output}",
        }
    major = int(match.group("major"))
    minor = int(match.group("minor"))
    patch = int(match.group("patch"))
    if major < 3 or (major == 3 and minor < 12):
        return {
            "ok": False,
            "commands": comp.args,
            "stdout": comp.stdout,
            "stderr": comp.stderr,
            "error": f"Python version {major}.{minor}.{patch} is not supported. Please use Python 3.12 or later.",
        }
    return {
        "ok": True,
        "commands": comp.args,
        "stdout": comp.stdout,
        "stderr": comp.stderr,
        "error": "",
    }


def _cmake() -> CheckResult:
    comp = subprocess.run(
        ["cmake", "--version"],
        capture_output=True,
        universal_newlines=True,
        encoding="utf-8",
    )
    output = comp.stdout.strip()
    lines = output.split("\n")
    if len(lines) < 1:
        return {
            "ok": False,
            "commands": comp.args,
            "stdout": comp.stdout,
            "stderr": comp.stderr,
            "error": f"cmake version not found in output: {output}",
        }
    line = lines[0]
    match = re.match(
        r"cmake version (?P<major>\d+)\.(?P<minor>\d+)\.(?P<patch>\d+)", line
    )
    if match is None:
        return {
            "ok": False,
            "commands": comp.args,
            "stdout": comp.stdout,
            "stderr": comp.stderr,
            "error": f"cmake version not found in output: {output}",
        }
    major = int(match.group("major"))
    minor = int(match.group("minor"))
    patch = int(match.group("patch"))
    if major < 3 or (major == 3 and minor < 28):
        return {
            "ok": False,
            "commands": comp.args,
            "stdout": comp.stdout,
            "stderr": comp.stderr,
            "error": f"cmake version {major}.{minor}.{patch} is not supported. Please use cmake 3.28 or later.",
        }
    return {
        "ok": True,
        "commands": comp.args,
        "stdout": comp.stdout,
        "stderr": comp.stderr,
        "error": "",
    }


def _ninja() -> CheckResult:
    comp = subprocess.run(
        ["ninja", "--version"],
        capture_output=True,
        universal_newlines=True,
        encoding="utf-8",
    )
    output = comp.stdout.strip()
    match = re.match(r"(?P<major>\d+)\.(?P<minor>\d+)\.(?P<patch>\d+)", output)
    if match is None:
        return {
            "ok": False,
            "commands": comp.args,
            "stdout": comp.stdout,
            "stderr": comp.stderr,
            "error": f"ninja version not found in output: {output}",
        }
    major = int(match.group("major"))
    minor = int(match.group("minor"))
    patch = int(match.group("patch"))
    if major < 1 or (major == 1 and minor < 11):
        return {
            "ok": False,
            "commands": comp.args,
            "stdout": comp.stdout,
            "stderr": comp.stderr,
            "error": f"ninja version {major}.{minor}.{patch} is not supported. Please use ninja 1.11 or later.",
        }
    return {
        "ok": True,
        "commands": comp.args,
        "stdout": comp.stdout,
        "stderr": comp.stderr,
        "error": "",
    }


def doctor() -> bool:
    results = [_python(), _cmake(), _ninja()]

    ok = True
    print("-" * 80)
    for result in results:
        print(f"Command: {' '.join(result['commands'])}")
        print(f"Stdout:")
        print(result["stdout"])
        if result["ok"]:
            print(f"OK")
        else:
            ok = False
            print(f"Stderr:")
            print(result["stderr"])
            print(f"Error: {result['error']}")
        print("-" * 80)
    return ok
