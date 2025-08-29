# Tests for personal use. They work on MacOs.
# To make script runnable write "chmod +x ./script_name.sh"
set -e

# Lite
echo "========================= LITE ==================================="
echo "Setup"
make -C ../src clean all
rm -f outputs/Lite/*

echo "Test 1"
../src/pictoascii -p -i pictures/4kpicture.jpg -f outputs/Lite/4kpicture.txt -l

echo "Test 2"
../src/pictoascii -p -i pictures/64x64.jpg -f outputs/Lite/64x64.txt -p -l

echo "Test 3"
../src/pictoascii --print --image pictures/cimg.png --file outputs/Lite/cimg.txt -l

echo "Test 4"
../src/pictoascii -p -i pictures/cplusplus.png -f outputs/Lite/cplusplus.txt -l

echo "Test 5"
../src/pictoascii -p -i pictures/maxresdefault.jpg -f outputs/Lite/maxresdefault.txt -l

echo "Test 6"
../src/pictoascii -p -i pictures/mememe.jpeg -f outputs/Lite/mememe.txt -l

echo "Clean"
make -C ../src clean
echo "========================= LITE END ==================================="
#
