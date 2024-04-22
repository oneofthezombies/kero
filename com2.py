import sys
import traceback
import shutil
import os
import subprocess
import abc
from typing import Callable
import zipfile
import json

import requests
import toml


# region Utility functions


def _delete_path(path: str):
    if not os.path.exists(path):
        return
    if os.path.isfile(path):
        print(f"Deleting file: {path}")
        os.remove(path)
        return
    if os.path.isdir(path):
        print(f"Deleting directory: {path}")
        shutil.rmtree(path)
        return
    if os.path.islink(path):
        print(f"Deleting link: {path}")
        os.unlink(path)
        return
    raise ValueError(f"{path} is not a file, directory, or link")


def _download_file(url: str, path: str):
    with requests.get(url, stream=True) as response:
        response.raise_for_status()
        with open(path, "wb") as file:
            for chunk in response.iter_content(chunk_size=8192):
                file.write(chunk)


def _unzip_file(zip_path: str, unzip_path: str):
    with zipfile.ZipFile(zip_path, "r") as zip_ref:
        zip_ref.extractall(unzip_path)


def _load_toml(file_path: str) -> dict:
    with open(file_path, "r") as file:
        return toml.load(file)


# endregion


# region Command line running


class CommandLineRunner(abc.ABC):
    @abc.abstractmethod
    def run(self, commandline: str):
        pass


class SubprocessCommandLineRunner(CommandLineRunner):
    def run(self, command_line: str):
        subprocess.run(command_line, shell=True, check=True)


# endregion


# region Arguments parsing


class Arguments:
    def __init__(
        self,
        program: str,
        file: str,
        command: str | None,
        subcommand: str | None,
        args: list[str],
    ):
        self.program = program
        self.file = file
        self.command = command
        self.subcommand = subcommand
        self.args = args


def _parse_arguments() -> Arguments:
    program = sys.orig_argv[0]
    file = sys.orig_argv[1]
    command = sys.orig_argv[2] if len(sys.orig_argv) > 2 else None
    has_subcommand = False
    if len(sys.orig_argv) > 3:
        has_subcommand = not sys.orig_argv[3].startswith("-")
    subcommand = sys.orig_argv[3] if has_subcommand else None
    args = sys.orig_argv[4:] if has_subcommand else sys.orig_argv[3:]
    return Arguments(
        program=program, file=file, command=command, subcommand=subcommand, args=args
    )


# endregion


# region Library processing


class LibraryCtx:
    def __init__(
        self,
        step: str,
        name: str,
        build_dir: str,
        install_path: str,
        command_line_runner: CommandLineRunner,
    ):
        self.step = step
        self.name = name
        self.build_dir = build_dir
        self.install_path = install_path
        self.__command_line_runner = command_line_runner
        self.extras = {}

    def run(self, command_line: str):
        print(f"{self.name} {self.step} on {os.getcwd()} with command: {command_line}")
        self.__command_line_runner.run(command_line)


LibraryFn = Callable[[LibraryCtx], None]


def _default_library_configure(ctx: LibraryCtx):
    ctx.run(
        f"cmake -S . -B {ctx.build_dir} -G Ninja -DCMAKE_INSTALL_PREFIX={ctx.install_path} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
    )


def _default_library_build(ctx: LibraryCtx):
    ctx.run(f"cmake --build {ctx.build_dir}")


def _default_library_install(ctx: LibraryCtx):
    ctx.run(f"cmake --install {ctx.build_dir}")


class Library:
    def __init__(
        self,
        name: str,
        build_dir="build",
        configure: LibraryFn = _default_library_configure,
        build: LibraryFn = _default_library_build,
        install: LibraryFn = _default_library_install,
    ):
        if len(name) == 0:
            raise ValueError("Library name cannot be empty")
        self.name = name
        self.build_dir = build_dir
        self.configure = configure
        self.build = build
        self.install = install


class GithubArchiveLibrary(Library):
    def __init__(
        self,
        name: str,
        url: str,
        build_dir="build",
        configure: LibraryFn = _default_library_configure,
        build: LibraryFn = _default_library_build,
        install: LibraryFn = _default_library_install,
    ):
        super().__init__(name, build_dir, configure, build, install)
        if len(url) == 0:
            raise ValueError("Library url cannot be empty")
        if not url.endswith(".zip"):
            raise ValueError("Library url must end with .zip")
        self.url = url


def _library_path(library_name: str, com2_path: str) -> str:
    return os.path.join(com2_path, "libraries", library_name)


def _fetch_github_archive_library(library_name: str, library_url: str, com2_path: str):
    temp_path = os.path.join(com2_path, "temp", library_name)
    fetching_path = os.path.join(temp_path, "FETCHING")
    library_path = _library_path(library_name, com2_path)
    metadata_path = os.path.join(com2_path, "libraries", f"{library_name}.toml")

    def delete_all():
        _delete_path(fetching_path)
        _delete_path(library_path)
        _delete_path(metadata_path)

    # fetching in progress
    if os.path.exists(fetching_path):
        print(f"Delete '{library_name}', it is in progress.")
        delete_all()

    # partially installed
    if not os.path.exists(library_path) or not os.path.exists(metadata_path):
        print(f"Delete '{library_name}', it is partially installed.")
        delete_all()

    # check metadata
    if os.path.exists(metadata_path):
        metadata = _load_toml(metadata_path)
        url = metadata.get("url")
        if url is None:
            print(f"Delete '{library_name}', metadata is missing 'url'.")
            delete_all()
        elif url != library_url:
            print(
                f"Delete '{library_name}', metadata url '{url}' does not match library url '{library_url}'."
            )
            delete_all()
        else:
            print(f"Skip '{library_name}', already installed.")
            return

    # initialize temp files
    _delete_path(temp_path)
    os.makedirs(temp_path, exist_ok=True)
    with open(fetching_path, "w") as file:
        file.write("")

    # download library
    zip_path = os.path.join(temp_path, f"{library_name}.zip")
    print(f"Downloading '{library_name}' to {zip_path}")
    _download_file(library_url, zip_path)

    # unzip library
    unzip_path = os.path.join(temp_path, "unzip")
    print(f"Unzipping {zip_path} to {unzip_path}")
    _unzip_file(zip_path, unzip_path)

    # move library
    entries = os.listdir(unzip_path)
    if len(entries) != 1:
        raise ValueError(f"Expected 1 entry in {unzip_path}, found {len(entries)}")
    temp_library_path = os.path.join(unzip_path, entries[0])
    print(f"Moving {temp_library_path} to {library_path}")
    shutil.move(temp_library_path, library_path)

    # save metadata
    with open(metadata_path, "w") as file:
        file.write(f'url = "{library_url}"\n')

    # cleanup temp files
    _delete_path(temp_path)


# endregion


# region Command processing


class CommandCtx:
    def __init__(
        self,
        project_build_path: str,
        com2_path: str,
        install_path: str,
        command_line_runner: CommandLineRunner,
        libraries: list[Library],
    ):
        self.project_build_path = project_build_path
        self.com2_path = com2_path
        self.install_path = install_path
        self.command_line_runner = command_line_runner
        self.libraries = libraries
        self.extras = {}


CommandFn = Callable[[CommandCtx], None]


class CommandInfo:
    def __init__(self, description: str, fn: CommandFn):
        self.description = description
        self.fn = fn


class CommandRegistry:
    def __init__(self):
        self.commands: dict[str, CommandInfo] = {}
        self.subcommands: dict[str, dict[str, CommandInfo]] = {}

    def register(self, command: str, subcommand: str | None, command_info: CommandInfo):
        if subcommand is None:
            self.commands[command] = command_info
        else:
            if command not in self.subcommands:
                self.subcommands[command] = {}
            self.subcommands[command][subcommand] = command_info

    def get(self, command: str, subcommand: str | None) -> CommandInfo | None:
        if subcommand is None:
            return self.commands.get(command)
        return self.subcommands.get(command, {}).get(subcommand)


def _default_clean_command(ctx: CommandCtx):
    _delete_path(ctx.project_build_path)
    _delete_path(ctx.com2_path)


def _default_libraries_install_command(ctx: CommandCtx):
    for library in ctx.libraries:
        cwd = os.getcwd()
        try:
            _fetch_github_archive_library(library.name, library.url, ctx.com2_path)

            library_path = _library_path(library.name, ctx.com2_path)
            print(f"Changing directory to {library_path}")
            os.chdir(library_path)

            print(f"Running configure for '{library.name}'")
            library_action_ctx = LibraryCtx(
                "configure",
                library.name,
                library.build_dir,
                ctx.install_path,
                ctx.command_line_runner,
            )
            library.configure(library_action_ctx)

            print(f"Running build for '{library.name}'")
            library_action_ctx.step = "build"
            library.build(library_action_ctx)

            print(f"Running install for '{library.name}'")
            library_action_ctx.step = "install"
            library.install(library_action_ctx)
        finally:
            os.chdir(cwd)


def _default_project_build_command(ctx: CommandCtx):
    # configure and build project
    ctx.command_line_runner.run(
        f"cmake -S . -B {ctx.project_build_path} -G Ninja -DCMAKE_PREFIX_PATH={ctx.install_path} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
    )
    ctx.command_line_runner.run(f"cmake --build {ctx.project_build_path}")

    # merge compile_commands.json files
    _merge_compile_commands(ctx)


def _merge_compile_commands(ctx: CommandCtx):
    # collect project compile_commands.json file
    comcoms_paths: list[str] = []
    comcom_path = os.path.join(ctx.project_build_path, "compile_commands.json")
    if not os.path.exists(comcom_path):
        print(f"Skipping missing compile_commands.json: {comcom_path}")
    else:
        comcoms_paths.append(comcom_path)

    # collect library compile_commands.json files
    for library in ctx.libraries:
        library_path = _library_path(library.name, ctx.com2_path)
        library_build_dir = os.path.join(library_path, library.build_dir)
        comcom_path = os.path.join(library_build_dir, "compile_commands.json")
        if not os.path.exists(comcom_path):
            print(f"Skipping missing compile_commands.json: {comcom_path}")
            continue
        comcoms_paths.append(comcom_path)

    # merge compile_commands.json files
    comcoms = []
    for comcoms_path in comcoms_paths:
        with open(comcoms_path, "r") as file:
            comcoms.extend(json.load(file))

    # write merged compile_commands.json
    with open("compile_commands.json", "w") as file:
        json.dump(comcoms, file, indent=2)


# endregion


# region Application


class App:
    def __init__(
        self,
        project_build_dir="build",
        install_path=os.path.join(os.getcwd(), ".com2", "local"),
        command_line_runner: CommandLineRunner = SubprocessCommandLineRunner(),
        libraries: list[Library] = [],
    ):
        self.arguments = _parse_arguments()
        self.__command_registry = CommandRegistry()
        self.__project_build_path = os.path.join(os.getcwd(), project_build_dir)
        self.__com2_path = os.path.join(os.getcwd(), ".com2")
        self.__install_path = install_path
        self.__command_line_runner = command_line_runner
        self.__libraries = libraries
        self.__validate_library_uniqueness()

    def command(self, command: str, subcommand: str | None = None, description=""):
        self.__check_command_uniqueness(command, subcommand)

        def decorator(fn):
            self.__command_registry.register(
                command, subcommand, CommandInfo(description, fn)
            )
            return fn

        return decorator

    def run(self):
        self.__register_default_commands()
        if self.arguments.command is None:
            self.print_help()
            sys.exit(1)

        command_info = self.__command_registry.get(
            self.arguments.command, self.arguments.subcommand
        )
        if command_info is None:
            self.print_help()
            sys.exit(1)

        cwd = os.getcwd()
        try:
            command_info.fn(
                CommandCtx(
                    self.__project_build_path,
                    self.__com2_path,
                    self.__install_path,
                    self.__command_line_runner,
                    self.__libraries,
                )
            )
        except Exception:
            command_line = " ".join(sys.orig_argv)
            print(f"Error running command line: {command_line}")
            traceback.print_exc()
            sys.exit(1)
        finally:
            os.chdir(cwd)

    def print_help(self):
        print(f"Usage: {self.arguments.program} {self.arguments.file} <command>")
        print("Commands:")
        subcommand_pad = (
            max(
                len(subcommand)
                for subcommands in self.__command_registry.subcommands.values()
                for subcommand in subcommands
            )
            + 2
        )
        command_pad = subcommand_pad + 2

        command_set = set(self.__command_registry.commands.keys())
        for command in self.__command_registry.subcommands.keys():
            command_set.add(command)
        commands = sorted(command_set)
        for command in commands:
            command_info = self.__command_registry.get(command, None)
            if command_info is not None:
                print(f"  {command.ljust(command_pad)}{command_info.description}")
            else:
                print(f"  {command}")

            subcommand_set = self.__command_registry.subcommands.get(command, {}).keys()
            subcommands = sorted(subcommand_set)
            for subcommand in subcommands:
                subcommand_info = self.__command_registry.get(command, subcommand)
                print(
                    f"    {subcommand.ljust(subcommand_pad)}{subcommand_info.description}"
                )

    def __validate_library_uniqueness(self):
        names = set()
        for library in self.__libraries:
            if library.name in names:
                raise ValueError(f"Library name '{library.name}' is duplicated")
            names.add(library.name)

    def __check_command_uniqueness(self, command: str, subcommand: str | None):
        command_info = self.__command_registry.get(command, subcommand)
        if command_info is not None:
            if subcommand is None:
                raise ValueError(f"Command '{command}' is already registered")
            raise ValueError(
                f"Command '{command}' subcommand '{subcommand}' is already registered"
            )

    def __register_default_commands(self):
        if not self.__command_registry.get("clean", None):
            print("'clean' command not found, registering default 'clean' command")
            self.command(
                "clean", description="Delete the com2 and project build directories"
            )(_default_clean_command)

        if not self.__command_registry.get("libraries", "install"):
            print(
                "'libraries install' command not found, registering default 'libraries install' command"
            )
            self.command(
                "libraries", subcommand="install", description="Install the libraries"
            )(_default_libraries_install_command)

        if not self.__command_registry.get("project", "build"):
            print(
                "'project build' command not found, registering default 'project build' command"
            )
            self.command(
                "project", subcommand="build", description="Build the project"
            )(_default_project_build_command)


# endregion
