# Tests for personal use. They work on MacOs.
# To make script runnable write "chmod +x ./script_name.sh"
set -e

# Test help
echo "========================= TEST HELP ==================================="
echo "Setup"
make -C ../src clean all

echo "Test 1"
../src/pictoascii -h

echo "Test 2"
../src/pictoascii --help

echo "Test 3"
../src/pictoascii -p --image pictures/cimg.png --file outputs/cimg3.txt -s " .'\`^\":,;Il!i><~+_-?][}{1()|/tfjrnxunvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@\$" -h

echo "Test 4"
../src/pictoascii -p --image pictures/cimg.png --help --file outputs/cimg4.txt -s " .'\`^\":,;Il!i><~+_-?][}{1()|/tfjrnxunvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@\$"

echo "Clean"
make -C ../src clean
echo "========================= TEST HELP END ==================================="
#


