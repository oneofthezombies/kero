# Grammar

Default Runtime is coroutine
every function is task and return future

```python
def add(a, b):
    return a + b

def multiply(a, b):
    return a * b

def subtract(a, b):
    return a - b

def divide(a, b):
    if b == 0:
        raise Exception("divide by zero")
    return a / b

subtract(add(1, 2))

if __name__ == '__main__':
    print("hello world!")
```
