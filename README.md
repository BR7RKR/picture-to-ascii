# Picture to ASCII

## Overview
This application creates an ASCII image from a regular image.

It supports the following formats:
* JPEG (tested)
* PNG (tested)
* TGA
* BMP
* PSD
* GIF (only a single frame, not an animation)
* HDR
* PIC (Softimage)
* PNM (PPM/PGM)

**Input:** path to the image  
**Output:** a TXT file with ASCII art

## How to Use
1. Install a C compiler (you may need to change `CC` in the Makefile to your compiler).

2. Open your terminal, navigate to the `src` folder, and run `make` (`make` exists by default on Linux and macOS, but not on Windows).

3. Run `./app path/to/picture output/file/path`.

4. Check the result in any text editor or in the console.

**Note:** It is better to use small images (~300x300px). Images with higher resolutions may be too large for the terminal or your text editor.

## Tests
There is a `tests` folder containing some tests that can be launched with the `.sh` file. You can use this file to test the program.  
I use them on macOS, so you may need to modify the script to run it on Linux or Windows.

## Plans for Further Development
1. Add more customization options for a better user experience with flags.  
2. Add a suppression option.  
3. Add a "save as picture" option.  
4. Create a cross-platform console application.
