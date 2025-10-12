# Tests for personal use. They work on MacOs.
# To make script runnable write "chmod +x ./script_name.sh"
set -e

# Custom symbols
echo "========================= CUSTOM SYMBOLS ==================================="
echo "Setup"
make -C ../src clean all
rm -f outputs/CustomSymbols/*
mkdir -p outputs/CustomSymbols

echo "Test 1"
../src/pictoascii --print --image pictures/cimg.png --file outputs/CustomSymbols/cimg1.txt --symbols " .:-=+*#%@"

echo "Test 2"
../src/pictoascii -p --image pictures/cimg.png --file outputs/CustomSymbols/cimg2.txt -s " .'\`^\":,;Il!i><~+_-?][}{1()|/tfjrnxunvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@\$"

echo "Test 3"
../src/pictoascii -p -i pictures/mememe.jpeg -f outputs/CustomSymbols/mememe3.txt -s " .'\`^\":,;Il!i><~+_-?][}{1()|/tfjrnxunvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@\$"

echo "Test 4"
../src/pictoascii -p -i pictures/mememe.jpeg -f outputs/CustomSymbols/mememe4.txt --symbols " .:-=+*#%@"

echo "Test 5"
../src/pictoascii -p --image pictures/cimg.png --file outputs/CustomSymbols/cimg5.txt -s " .'\`^\@\$"

echo "Clean"
make -C ../src clean
echo "========================= CUSTOM SYMBOLS END ==================================="
#
