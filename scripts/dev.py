import argparse
import shutil


def clean():
    shutil.rmtree("third_party")


def doctor():
    pass


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
