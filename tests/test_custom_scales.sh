# Tests for personal use. They work on MacOs.
# To make script runnable write "chmod +x ./script_name.sh"
set -e

# Custom scales
echo "========================= CUSTOM SCALES ==================================="
echo "Setup"
make -C ../src clean all
rm -f outputs/CustomScales/*

echo "Test 1"
../src/pictoascii --print --image pictures/cimg.png --file outputs/CustomScales/cimg1.txt

echo "Test 2"
../src/pictoascii -p --image pictures/cimg.png --file outputs/CustomScales/cimg2.txt

echo "Test 3"
../src/pictoascii -p --image pictures/cimg.png --file outputs/CustomScales/cimg3.txt -ws 0.6 -hs 0.3

echo "Test 4"
../src/pictoascii -p --image pictures/cimg.png --file outputs/CustomScales/cimg4.txt --width-scale 0.6 --height-scale 0.3

echo "Test 5"
../src/pictoascii -p --image pictures/cimg.png --file outputs/CustomScales/cimg5.txt -ws 0.2 -hs 0.1

echo "Test 6"
../src/pictoascii -p --image pictures/cimg.png --file outputs/CustomScales/cimg6.txt -ws 0.9 -hs 0.7

echo "Test 7"
../src/pictoascii -p --image pictures/cimg.png --file outputs/CustomScales/cimg7.txt -ws 1 -hs 1

echo "Test 8"
../src/pictoascii -p --image pictures/cimg.png --file outputs/CustomScales/cimg8.txt -ws 1.6 -hs 1.3

echo "Clean"
make -C ../src clean
echo "========================= CUSTOM SCALES END ==================================="
#
