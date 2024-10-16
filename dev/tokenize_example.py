import tokenize
from io import BytesIO

with open("example.py", "rb") as f:
    file_content = f.read()

file_stream = BytesIO(file_content)
tokens = tokenize.tokenize(file_stream.readline)
for token in tokens:
    print(token)

"""
TokenInfo(type=67 (ENCODING), string='utf-8', start=(0, 0), end=(0, 0), line='')
TokenInfo(type=1 (NAME), string='print', start=(1, 0), end=(1, 5), line='print("hello world")\n')
TokenInfo(type=55 (OP), string='(', start=(1, 5), end=(1, 6), line='print("hello world")\n')
TokenInfo(type=3 (STRING), string='"hello world"', start=(1, 6), end=(1, 19), line='print("hello world")\n')
TokenInfo(type=55 (OP), string=')', start=(1, 19), end=(1, 20), line='print("hello world")\n')
TokenInfo(type=4 (NEWLINE), string='\n', start=(1, 20), end=(1, 21), line='print("hello world")\n')
TokenInfo(type=0 (ENDMARKER), string='', start=(2, 0), end=(2, 0), line='')
"""
