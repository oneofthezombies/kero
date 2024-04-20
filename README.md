# Kero

Kero is a programming language written in C++.
It is a simple and intuitive system programming language with the philosophy “Less is better than more.”

![mascot](/resources/mascot.webp)

# How to Build

## Install Dependencies

```sh
node scripts/install.mjs
```

## Kero

```sh
mkdir -p build && cd build
cmake .. -G Ninja -DCMAKE_PREFIX_PATH="$HOME/.local"
cmake --build .
```
