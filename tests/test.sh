# Tests for personal use. They work on MacOs.
set -e

# Simple test
make -C ../src clean all
rm -f outputs/*

../src/app pictures/4kpicture.jpg outputs/4kpicture.txt
../src/app pictures/64x64.jpg outputs/64x64.txt
../src/app pictures/cimg.png outputs/cimg.txt
../src/app pictures/cplusplus.png outputs/cplusplus.txt
../src/app pictures/maxresdefault.jpg outputs/maxresdefault.txt
../src/app pictures/mememe.jpeg outputs/mememe.txt
#
