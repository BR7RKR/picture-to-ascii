# Picture to ASCII

## Overview
This application creates an ASCII image from a regular image.

It supports the following formats as an input:
* JPEG (tested)
* PNG (tested)
* TGA
* BMP
* PSD
* GIF (only a single frame, not an animation)
* HDR
* PIC (Softimage)
* PNM (PPM/PGM)

More info about input and output in the flags section.

## Example ascii image
```bash
.::::::::::::::::::::::::::.::.:::::.::.:::::.:
::.:.:.:.::.:.:.:.::.:.:.:.:.::.:.:.::::.:.:.::
::.:::::.::.:::::.::-######+:::::::::::::::::::
::.:::::.::.:::::%#############.:::::::::::::::
::.:.:.:.::.::####################=.::::.:.:.::
::::::::::%########=::::::::=#########:::::::::
:::::::.########.::::::::::.::.:########:::::.:
:::::::.######:::::::.%##%:.::.:::######:::::.:
:::::::.#####:::::.##########:.:.#######:::::.:
:::::::.####=::::%######################:::::::
::.:::::####:::::#######################.:::.::
::.:::::####:::::#######################.::::::
::.:::::####=::::%######################.::::::
::.:::::#####::::.:##########::::#######.::::::
::::::::######::::::::%###-::::::.######.::::::
.::.:.:.########.::.:.:.:.:.::.:########:.:.:.:
::::::::::#########::::::::.:#########:.:::::.:
:::::::::::::+####################=:.::.:::::.:
.::.:.:.::::.:.:.##############:.:.:.::.:.:.:.:
::.:::::.::.:::::.::########::::::::::::::::.::
::.:::::.::.:::::.::.:.:.::::::::::::::::::::::
```

## How to use

1. [Install](#installation) the app or [build](#how-to-build) it manually.

2. Run `./pictoascii -i path/to/picture -f output/file/path -p` to make ascii art from image, print it to the console and write it to file.

3. Use the `--help` flag to see detailed usage instructions.

## How to build

1. Install a C compiler (you may need to change `CC` in the Makefile to your compiler).

2. Install libjpeg-turbo (api version 3.1 is used here) and change path to the lib in the Makefile (if you have arm64 macos and you've
installed everything from the homebrew change nothing)

3. Open your terminal, navigate to the `src` folder, and run `make` (`make` exists by default on Linux and macOS, but not on Windows).

4. Run `./pictoascii -i path/to/picture -f output/file/path -p`.

5. Check the result in any text editor or in the console.

**Note:** It is better to use small images (~300x300px). Images with higher resolutions may be too large for the terminal or your text editor.
If you want to save pictures in an image format it is safe to use any resolution.

## Tests
There is a `tests` folder containing some tests that can be launched with the `.sh` file. You can use this file to test the program.  
Use `make test` to run all tests on any operating system.

**Note:** Test scripts are made for the bash. You'll need to use it to run the scripts.

## Flags

This programm supports different flags:

### -h or --help
Prints out a help message that describes all the commands available.

```bash
Usage: pictoascii [options]

Options:
  -h, --help                Show this help message and exit
  -p, --print               Print output to console
  -f, --file <path>         Save output to file at specified path
  -i, --image <path>        Path to input image file
  -s, --symbols <chars>     Specify custom ASCII characters for output
  -ws, --width-scale <f>    Scale width by a float factor (e.g., 0.5)
  -hs, --height-scale <f>   Scale height by a float factor (e.g., 0.5)
  -l, --lite                Use simple ascii characters for outputm
  -r, --reverse             Reverse symbols that are used to draw the image
  -fl, --font-latin         Use with '-if' flag. Extends default font with latin characters

Examples:
  pictoascii -p -i image.png -f output.txt
  pictoascii --image image.png --lite -p
```

### -p or --print
Prints out image to the console (ascii image).

### -f or --file
Saves ascii image as a file.
Rquires path to the file. The file will be created if it doesn't exist.

Supported formats:
* JPEG
* PNG
* TGA
* BMP
* TXT

**Note:** use -ws and -hs flags with 1 if you want to get the native resolution.
**Note:** use jpeg/jpg if you want to save huge images faster (4k for example).

### -i or --image
With this flag you must provide path to your image. This flags reades a image from the file.

### -s or --symbols
This flag allows you to customise the string with ascii symbols by replacing it with your own ascii symbols string.

### -ws or --width-scale
Changes the width scale of the ascii image with your custom float.

### -hs or --height-scale
Changes the height scale of the ascii image with your custom float.

### -l or --lite
Changes default string of the ascii symbols to its lighter version.

**Note:** -s flag overrides this flag

### -r or --reverse
Use this flag if you want to reverse the ascii chars string.

### -fl or --font-latin
This flag extends basic font with latin characters. It works in pair with '-f' flag when you save as an image.

## Installation

### MacOS (arm64)

Homebrew approach:

*Homebrew will make the application global so it can be run from anywhere.*

1. Add Tap to the repo with my homebrew app

```bash
brew tap hakari/tap https://github.com/BR7RKR/homebrew-picture-to-ascii
```

2. Install the app

```bash
brew install --cask pictoascii
```

3. My app doesn’t have an Apple digital signature, so it will need to be marked as safe with the following command
```bash
xattr -d com.apple.quarantine /opt/homebrew/bin/pictoascii
```

4. Run app with the --help flag to check if it works

Manual approach (not recommended):
  1. Go to [releases]("https://github.com/BR7RKR/picture-to-ascii/releases") and find `.tar.gz` file for macOs there;
  2. Download this file;
  3. Double tap the file to get the app;
  4. Run terminal and write the following command;
  ```bash
  sudo xattr -r -d com.apple.quarantine ./pictoascii
  ```
  5. Run app with the --help flag to check if it works;

### Windows

1. Go to the [releases]("https://github.com/BR7RKR/picture-to-ascii/releases");

2. Download .exe file from any release that has it;

3. If you want to use it from anyware place it in any folder that is in the list of enviromental variables or provide path to the app there;

4. Run app with the --help flag to check if it works;

#### Linux

**Note:** `.tar.gz` file for fedora linux has fedora in its name. 
The other linux file is for debian (ubuntu) but it was not tested.

1. Go to [releases]("https://github.com/BR7RKR/picture-to-ascii/releases") and find `.tar.gz` file for linux there;
2. Download this file;
3. Double tap the file to get the app;
4. Run app with the --help flag to check if it works;

## Plans for Further Development
* Improve flags handling
* Add a compression option to compress the initial image.
