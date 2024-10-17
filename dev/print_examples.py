import tokenize
from io import BytesIO


def print_example(source: bytes):
    io = BytesIO(source)
    tokens = tokenize.tokenize(io.readline)
    print(source)
    for token in tokens:
        print(token)


print_example(b"")
print_example(b"\n")
