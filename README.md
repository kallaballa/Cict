ColorDict
============

A Linux (and possibly Mac OSX) command line tool that translates color values (24bit RGB hex) to human readable names. The program reads a list of name/color mappings
from the file colordict.txt - that list of course doesn't provide a distinct name for all the possible color shades.
Instead it searches for the closest color (euclidean metric used on the RGB values) and chooses that name.
Additionally it outputs the hex value of the found color aswell as the distance to the given color.

##Build

    git clone https://github.com/kallaballa/ColorDict.git
    cd ColorDict
    make

##Usage

Simply pass a 24bit RGB hex value as the first and only parameter. 

    ./colorDict 000081

Output:

    1 #000080 navyblue
