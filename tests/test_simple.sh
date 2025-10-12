# Tests for personal use. They work on MacOs.
# To make script runnable write "chmod +x ./script_name.sh"
set -e

# Simple test
echo "========================= SIMPLE TEST ==================================="
echo "Setup"
make -C ../src clean all
rm -f outputs/SimpleTest/*
mkdir -p outputs/SimpleTest

echo "Test 1"
../src/pictoascii -i pictures/4kpicture.jpg -f outputs/SimpleTest/4kpicture.txt

echo "Test 2"
../src/pictoascii -i pictures/64x64.jpg -f outputs/SimpleTest/64x64.txt -p

echo "Test 3"
../src/pictoascii --print --image pictures/cimg.png --file outputs/SimpleTest/cimg.txt

echo "Test 4"
../src/pictoascii -p -i pictures/cplusplus.png -f outputs/SimpleTest/cplusplus.txt

echo "Test 5"
../src/pictoascii -i pictures/maxresdefault.jpg -f outputs/SimpleTest/maxresdefault.txt

echo "Test 6"
../src/pictoascii -i pictures/mememe.jpeg -f outputs/SimpleTest/mememe.txt

echo "Test 7 with useless flag"
../src/pictoascii -i pictures/cplusplus.png -f outputs/SimpleTest/cplusplus7.txt -fl

echo "Clean"
make -C ../src clean
echo "========================= SIMPLE TEST END ==================================="
#
