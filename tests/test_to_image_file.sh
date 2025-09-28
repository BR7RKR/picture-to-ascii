# Tests for personal use. They work on MacOs.
# To make script runnable write "chmod +x ./script_name.sh"
# Use to check all files: https://image-viewer.com/ru/
set -e

# To image file test
echo "========================= TEST TO IMAGE FILE ==================================="
echo "Setup"
make -C ../src clean all
rm -f outputs/ToImageFile/*

echo "Test 1"
../src/pictoascii -i pictures/4kpicture.jpg -l -f outputs/ToImageFile/4kpicture1.jpg

echo "Test 2"
../src/pictoascii -i pictures/64x64.jpg -l -f outputs/ToImageFile/64x642.png

echo "Test 3"
../src/pictoascii --image pictures/cimg.png -l -f outputs/ToImageFile/cimg3.png

echo "Test 4"
../src/pictoascii -i pictures/mememe.jpeg --file outputs/ToImageFile/mememe4.jpg -l -r

echo "Test 5"
../src/pictoascii -i pictures/mememe.jpeg --file outputs/ToImageFile/mememe5.tga

echo "Test 6"
../src/pictoascii -i pictures/mememe.jpeg --file outputs/ToImageFile/mememe6.bmp

echo "Test 7"
../src/pictoascii --image pictures/cimg.png -f outputs/ToImageFile/cimg7.jpeg

echo "Test 8"
../src/pictoascii --image pictures/cimg.png -f outputs/ToImageFile/cimg8.icb

echo "Test 9"
../src/pictoascii --image pictures/cimg.png -f outputs/ToImageFile/cimg9.vda

echo "Test 10"
../src/pictoascii --image pictures/cimg.png -f outputs/ToImageFile/cimg10.vst

echo "Test 11"
../src/pictoascii --image pictures/cimg.png -f outputs/ToImageFile/cimg11.dip

echo "Test 12"
../src/pictoascii --image pictures/cimg.png -f outputs/ToImageFile/cimg12.rle

echo "Test 13"
../src/pictoascii -i pictures/64x64.jpg -l -f outputs/ToImageFile/64x6413.png -ws 1 -hs 1 -r

echo "Test 14"
../src/pictoascii -i pictures/4kpicture.jpg --font-latin -f outputs/ToImageFile/4kpicture_latin.jpg -s " \`'.,-~:;!lI+_?^\"/|(){}[]tfjrxnuvczXYUJCLQ0OZáàâäåãæçéèêëíìîïñóòôöõøúùûüý*#MW&8%B@$"

echo "Test 15: without proper font"
../src/pictoascii -i pictures/4kpicture.jpg -f outputs/ToImageFile/4kpicture_latin_15.jpg -s " \`'.,-~:;!lI+_?^\"/|(){}[]tfjrxnuvczXYUJCLQ0OZáàâäåãæçéèêëíìîïñóòôöõøúùûüý*#MW&8%B@$"

echo "Test 16 test to txt and image"
../src/pictoascii --image pictures/cimg.png -f outputs/ToImageFile/cimg16.png -f outputs/ToImageFile/cimg16.txt

echo "Clean"
make -C ../src clean
echo "========================= TEST TO IMAGE FILE END ==================================="
#
