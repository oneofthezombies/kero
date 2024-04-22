import com2


app = com2.App(
    libraries=[
        com2.GithubArchiveLibrary(
            name="cpp-tree-sitter",
            url="https://github.com/oneofthezombies/cpp-tree-sitter/archive/refs/tags/v0.2.4.zip",
        ),
        com2.GithubArchiveLibrary(
            name="googletest",
            url="https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip",
        ),
    ],
)


if __name__ == "__main__":
    app.run()
