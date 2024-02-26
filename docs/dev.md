# Development

# Prequirements

## Python

### Version

```sh
python --version
# Python 3.12.2
```

### Setup Virtual Environment

```sh
python -m venv .venv
. .venv/bin/activate
pip install -r requirements.txt
pre-commit install -t pre-push
```

## Python Source Build Dependencies

### Ubuntu

```sh
sudo apt-get update && \
    sudo apt-get install -y \
        libgdbm-compat-dev
```

### Macos

```sh
brew install tcl-tk
```
