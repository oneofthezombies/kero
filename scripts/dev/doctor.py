import os
import re
import subprocess
from typing import List

from common import THIRD_PARTY_DIR


class CheckResult:
    def __init__(self, ok: bool, error: str):
        self.ok = ok
        self.error = error


class CheckDirResult(CheckResult):
    def __init__(self, ok: bool, error: str, path: str):
        super().__init__(ok, error)
        self.path = path


class CheckCommandResult(CheckResult):
    def __init__(
        self,
        ok: bool,
        error: str,
        commands: List[str],
        stdout: str,
        stderr: str,
    ):
        super().__init__(ok, error)
        self.commands = commands
        self.stdout = stdout
        self.stderr = stderr

    @staticmethod
    def from_completed(
        ok: bool,
        error: str,
        comp: subprocess.CompletedProcess[str],
    ) -> "CheckCommandResult":
        return CheckCommandResult(
            ok=ok,
            error=error,
            commands=comp.args,
            stdout=comp.stdout,
            stderr=comp.stderr,
        )

    @staticmethod
    def from_completed_ok(
        completed: subprocess.CompletedProcess[str],
    ) -> "CheckCommandResult":
        return CheckCommandResult.from_completed(True, "", completed)

    @staticmethod
    def from_completed_error(
        completed: subprocess.CompletedProcess[str],
        error: str,
    ) -> "CheckCommandResult":
        return CheckCommandResult.from_completed(False, error, completed)


def _python() -> CheckResult:
    completed = subprocess.run(
        ["python", "--version"],
        capture_output=True,
        universal_newlines=True,
        encoding="utf-8",
    )
    if completed.returncode != 0:
        return CheckCommandResult.from_completed_error(
            completed,
            "Python version command failed",
        )
    output = completed.stdout.strip()
    match = re.match(r"Python (?P<major>\d+)\.(?P<minor>\d+)\.(?P<patch>\d+)", output)
    if match is None:
        return CheckCommandResult.from_completed_error(
            completed,
            f"Python version not found in output: {output}",
        )
    major = int(match.group("major"))
    minor = int(match.group("minor"))
    patch = int(match.group("patch"))
    if major < 3 or (major == 3 and minor < 12):
        return CheckCommandResult.from_completed_error(
            completed,
            f"Python version {major}.{minor}.{patch} is not supported. Please use Python 3.12 or later.",
        )
    return CheckCommandResult.from_completed_ok(completed)


def _cmake() -> CheckResult:
    completed = subprocess.run(
        ["cmake", "--version"],
        capture_output=True,
        universal_newlines=True,
        encoding="utf-8",
    )
    if completed.returncode != 0:
        return CheckCommandResult.from_completed_error(
            completed,
            "cmake version command failed",
        )
    output = completed.stdout.strip()
    lines = output.split("\n")
    if len(lines) < 1:
        return CheckCommandResult.from_completed_error(
            completed,
            f"cmake version not found in output: {output}",
        )
    line = lines[0]
    match = re.match(
        r"cmake version (?P<major>\d+)\.(?P<minor>\d+)\.(?P<patch>\d+)", line
    )
    if match is None:
        return CheckCommandResult.from_completed_error(
            completed,
            f"cmake version not found in output: {output}",
        )
    major = int(match.group("major"))
    minor = int(match.group("minor"))
    patch = int(match.group("patch"))
    if major < 3 or (major == 3 and minor < 28):
        return CheckCommandResult.from_completed_error(
            completed,
            f"cmake version {major}.{minor}.{patch} is not supported. Please use cmake 3.28 or later.",
        )
    return CheckCommandResult.from_completed_ok(completed)


def _ninja() -> CheckResult:
    completed = subprocess.run(
        ["ninja", "--version"],
        capture_output=True,
        universal_newlines=True,
        encoding="utf-8",
    )
    if completed.returncode != 0:
        return CheckCommandResult.from_completed_error(
            completed,
            "ninja version command failed",
        )
    output = completed.stdout.strip()
    match = re.match(r"(?P<major>\d+)\.(?P<minor>\d+)\.(?P<patch>\d+)", output)
    if match is None:
        return CheckCommandResult.from_completed_error(
            completed,
            f"ninja version not found in output: {output}",
        )
    major = int(match.group("major"))
    minor = int(match.group("minor"))
    patch = int(match.group("patch"))
    if major < 1 or (major == 1 and minor < 11):
        return CheckCommandResult.from_completed_error(
            completed,
            f"ninja version {major}.{minor}.{patch} is not supported. Please use ninja 1.11 or later.",
        )
    return CheckCommandResult.from_completed_ok(completed)


def _llvm() -> CheckResult:
    llvm_dir = os.path.join(os.getcwd(), THIRD_PARTY_DIR, "llvm")
    if not os.path.exists(llvm_dir):
        return CheckDirResult(False, f"LLVM directory not found: {llvm_dir}", llvm_dir)
    return CheckDirResult(True, "", llvm_dir)


def doctor() -> bool:
    results = [_python(), _cmake(), _ninja(), _llvm()]
    ok = True
    print("-" * 80)
    for result in results:
        if isinstance(result, CheckCommandResult):
            print(f"Command: {' '.join(result.commands)}")
            print(f"Stdout:")
            print(result.stdout)
            if result.ok:
                print(f"OK")
            else:
                ok = False
                print(f"Stderr:")
                print(result.stderr)
                print(f"Error: {result.error}")
        elif isinstance(result, CheckDirResult):
            print(f"Directory: {result.path}")
            if result.ok:
                print(f"OK")
            else:
                ok = False
                print(f"Error: {result.error}")
        else:
            raise ValueError(f"Unexpected result type: {type(result)}")
        print("-" * 80)
    return ok


if __name__ == "__main__":
    doctor()
