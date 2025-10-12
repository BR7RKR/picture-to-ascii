# Tests for personal use. They work on MacOs.
# To make script runnable write "chmod +x ./script_name.sh"
set -e

# Test reverse symbols
echo "========================= TEST REVERSE SYMBOLS ==================================="
echo "Setup"
make -C ../src clean all
rm -f outputs/ReverseSymbols/*
mkdir -p outputs/ReverseSymbols

echo "Test 1"
../src/pictoascii -p --image pictures/cimg.png -r --file outputs/ReverseSymbols/cimg1.txt

echo "Test 2"
../src/pictoascii -p --image pictures/cimg.png --reverse --file outputs/ReverseSymbols/cimg2.txt

echo "Test 3"
../src/pictoascii -p --image pictures/cimg.png -r --file outputs/ReverseSymbols/cimg3.txt -l

echo "Test 4"
../src/pictoascii -p --image pictures/cimg.png --file outputs/ReverseSymbols/cimg4.txt -s " .'\`^\@\$" -r


echo "Clean"
make -C ../src clean
echo "========================= TEST REVERSE SYMBOLS END ==================================="
#


