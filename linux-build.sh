#!/bin/bash
# To make script runnable: chmod +x ./linux-build.sh

set -e

echo "[START BUILD]"

echo "> Installing dependencies"
# Fedora / RHEL
if command -v dnf &>/dev/null; then
    sudo dnf install -y gcc libjpeg-turbo-devel
# Debian / Ubuntu
elif command -v apt &>/dev/null; then # !WAS NOT TESTED
    sudo apt update
    sudo apt install -y build-essential libjpeg-turbo8-dev
else
    echo "Unsupported package manager. Please install gcc and libjpeg-turbo-devel manually."
    exit 1
fi

echo "> Go to src"
cd src

echo "> Run make release"
make release

echo "> Test run with the --help flag"
./pictoascii --help

echo "> Pack console app"
tar czf pictoascii-linux.tar.gz pictoascii

echo "> Cleanup"
make clean

echo "[FINISH BUILD]"