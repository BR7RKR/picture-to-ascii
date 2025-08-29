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

## Example ascii image
```bash
.'`,,.',,^'.,,'',,''',,.',,.'",,'.,,`'',,'',,.'^,,'.,,.',,"'.,,.'`,,'',,.'","'.,,'',,`'.,,.'",
``^""``""^``""``""```""``""``^""``""```""``""``^""``""``""^``""``^""``""``"""``""``""^``""``^"
,,"..,,..^,,..,,..,,"..,,..,,`..,,..",,..,,..,,^..,,..,,..`,,..,,"..,,..,,'.',,..,,..",,..,,`.
''`,,'',,"'.,,'',,''`,,.',,.'",,'.,,`'',,'';dwwwwwb,,,.',,"'.,,.'`,,'',,.'","'.,,'',,^'.,,.'",
,,"'.,,.'^,,'',,.'","'.,,'',,`'.,,.'",,.<qwwwwwwwwwwwwt"''`,,'',,"'.,,'.,,`'',,'',,.'",,'',,`'
''`,,'',,^'.,,'',,''`,,.',,.'",,'',,.dwwwwwwwwwwwwwwwwwwwp`'.,,.'`,,'',,.'","'.,,'',,^'.,,.'",
,,"'.,,.'^,,'',,.'","'.,,'',,`'.,[pwwwwwwwwwwwwwwwwwwwwwwwwwqv.,,"'.,,'.,,`'',,'',,.'",,'',,`'
''`,,'',,^'.,,'',,''`,,.',,.'`Ywwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwd",,'',,.'","'.,,'',,^'.,,.'",
,,"..,,..^,,..,,..,,"..,,.'pwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwq["..,,'.',,..,,..",,..,,`.
''`""''""^''""''""`'`""<qwwwwwwwwwwwwwwwwwwqpdpQpdpqwwwwwwwwwwwwwwwwwwwY.'"""''""''""^''""''""
''`""''""^''""''""`.bwwwwwwwwwwwwwwwwp{""''""''^""''""''[dwwwwwwwwwwwwwwwwq;"`'""''""^''""''""
,,"..,,..^,,..,,_pwwwwwwwwwwwwwwwwU.",,..,,..,,^..,,..,,..`,vqwwwwwwwwwwwwwwwwq.',,..",,..,,`.
''`,,'',,"'.,,.dwwwwwwwwwwwwwwwb..,,`'',,'',,.'^,,'',,.',,"'.,"qwwwwwwwwwwwwwwwp"'',,^'.,,.'",
,,"'.,,.'^,,''"qwwwwwwwwwwwwwd..,,.'",,'.,,'',,^'.,,'',,''`,,'',"Zwwwwwwwwwwwwwq.,,.'",,'',,`'
''`,,'',,^'.,,.qwwwwwwwwwwwq"",,'',,`'',,..Upqwwwqpq;".',,"'.,,.'`"qwwwwwwwwwwwq"'',,^'.,,.'",
,,"'.,,.'^,,''"qwwwwwwwwwwq,,`'.,,.'","dwwwwwwwwwwwwwwwp.'`,,'',,"'.qwwwwwwwwwwq.,,.'^,,'',,`'
''`,,'',,"'.,,.qwwwwwwwwwd".'",,'',,.wwwwwwwwwwwwwwwwwwwww"'.,,..<wwwwwwwwwwwwwq"'',,^'.,,.'",
,,"..,,..^,,.."qwwwwwwwww..,,`..,,.dwwwwwwwwwwwwwwwwwwwwwwwp,.dwwwwwwwwwwwwwwwwq.,,..",,..,,`.
``^""``""^``"".qwwwwwwww}""``^""`'dwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwq```""^``""``^"
..`,,..,,^..,,.qwwwwwwww.,,..",,.dwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwq"..,,`..,,..",
,,"'.,,.'^,,'."qwwwwwwwq,.',,`'."qwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwq.,,.'",,..,,`'
..`,,..,,"..,,.qwwwwwwwp.,,..",,.wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwq"..,,^..,,..",
,,"'.,,.'^,,''"qwwwwwwwq,'',,`'."wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwq.,,.'",,'',,`'
''`,,'',,^'.,,.qwwwwwwww.,,.'",,'dwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwq"'',,^'.,,.'",
,,"'.,,.'^,,''"qwwwwwwww['',,`'.,"pwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwq.,,.'",,'',,`'
''`,,'',,^'.,,.qwwwwwwwwq,,.'",,'',pwwwwwwwwwwwwwwwwwwwwwwwq.;qwwwwwwwwwwwwwwwwq"'',,^'.,,.'",
,,"'.,,.'^,,''"qwwwwwwwwwq',,`'.,,.'"wqwwwwwwwwwwwwwwwwwwwI,,'',^Qwwqwwwwwwwwwwq.,,.'",,'',,`'
..`,,..,,"..,,.qwwwwwwwwwwp..",,..,,`..pwwwwwwwwwwwwwwwq","..,,..`,,pwwwwwwwwwwq"..,,^..,,..",
"""''""''^",''"qwwwwwwwwwwwq"`''""''"""''"Idpwwwwwqdl.,"''`",'',"".pwwwwwwwwwwwq.""''^",'',"`'
"""`'""'`^""`'^qwwwwwwwwwwwwwZ''""'`"""`'""'`""^`'""``""```""'`""nwwwwwwwwwwwwwq.""'`^""''""``
..`,,..,,"..,,.pwwwwwwwwwwwwwwwZ..,,`..,,..,,..^,,..,,..,,"..,,vwwwwwwwwwwwwwwwp"..,,^..,,..",
,,"'.,,.'^,,'',,dwwwwwwwwwwwwwwwwq)'",,'.,,'',,^'.,,'',,''`,[qwwwwwwwwwwwwwwwqZ'',,.'",,'',,`'
''`,,'',,^'.,,'',,'IqwwwwwwwwwwwwwwwwpI,,'',,.'^,,'',,..Iqwwwwwwwwwwwwwwwwq;"'.,,'',,^'.,,.'",
,,"'.,,.'^,,'',,.'","'.ZwwwwwwwwwwwwwwwwwwqpdUntnYdpqwwwwwwwwwwwwwwwwwwY",`'',,'',,.'",,'',,`'
''`,,'',,^'.,,'',,''`,,''"fwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww[.,,.'","'.,,'',,^'.,,.'",
,,"'.,,.'^,,'',,.'","'.,,'',,!dwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwdI'.,,'.,,`'',,'',,.'",,'',,`'
..`,,..,,"..,,..,,'.',,..,,..",,.qwwwwwwwwwwwwwwwwwwwwwwwwwwqZ"..`,,..,,..",,..,,..,,^..,,..",
""^``""``^""``""``"""``""``""^``""``;qwwwwwwwwwwwwwwwwwwwq"""``""^``""``""```""``""``^""``""^`
,,"'.,,.'^,,'.,,.'","'.,,.',,`'.,,.'",,.LwwwwwwwwwwwwwL"''`,,.',,"'.,,'.,,''',,'',,.'^,,..,,`'
.'`,,..,,"'.,,'',,''',,.',,.'",,'.,,`'',,'.)pwwwwwp},,.',,"'.,,.'`,,'.,,.'","'.,,.',,^'.,,.'",
,,"'.,,.'^,,'',,.'","'.,,'',,`'.,,.'",,'.,,'.,"'..,,'',,''`,,'',,"'.,,'.,,`'',,'',,.'",,'',,`'
''`,,'',,^'.,,'',,''`,,.',,.'",,'',,`'',,'',,.'^,,'',,.',,"'.,,.'`,,'',,.'","'.,,'',,^'.,,.'",
```

## How to Use
1. Install a C compiler (you may need to change `CC` in the Makefile to your compiler).

2. Open your terminal, navigate to the `src` folder, and run `make` (`make` exists by default on Linux and macOS, but not on Windows).

3. Run `./pictoascii -i path/to/picture -f output/file/path -p`.

4. Check the result in any text editor or in the console.

**Note:** It is better to use small images (~300x300px). Images with higher resolutions may be too large for the terminal or your text editor.

## Tests
There is a `tests` folder containing some tests that can be launched with the `.sh` file. You can use this file to test the program.  
I use them on macOS, so you may need to modify the script to run it on Linux or Windows.

P.S. I'll try to make them runnable on other operatings systems.

## Flags

This programm supports different flags:

### -h or --help
Prints out a help message that describes all the commands available.

```bash
Usage: pictoascii [options]

Options:
  -h, --help               Show this help message and exit
  -p, --print              Print output to console
  -f, --file <path>        Save output to file at specified path
  -i, --image <path>       Path to input image file
  -s, --symbols <chars>    Specify custom ASCII characters for output
  -ws, --width-scale <f>   Scale width by a float factor (e.g., 0.5)
  -hs, --height-scale <f>  Scale height by a float factor (e.g., 0.5)
  -l, --light              Use simple ascii characters for output
  -r, --reverse            Reverse symbols that are used to draw the image

Examples:
  pictoascii -p -i image.png -f output.txt
  pictoascii --image image.png --lite -p
```

### -p or --print
Prints out image to the console (ascii image).

### -f or --file
Saves ascii image as a txt file.
Rquires path to the file. Programm will create a file if it doesn't exist

### -i or --image
With this flag you must provide path to your image. This flags reades a image from the file.

### -s or --symbols
This flag allows you to customise the string with ascii symbols by replacing it with your own ascii symbols string.

### -ws or --width-scale
Changes the width scale of the ascii image with your custom float.

### -hs or --height-scale
Changes the height scale of the ascii image with your custom float.

### -l or --light
Changes default string of the ascii symbols to its lighter version.

**Note:** -s flag overrides this flag

### -r or --reverse
Use this flag if you want to reverse the ascii chars string.

## Plans for Further Development
* Add a compression option.  
* Add a "save as picture" option.  
* Create a cross-platform console application.
