Hello there. Some tips about my code:

To compile the crawler program (Step 3), do:

g++ -g -Wall crawler.cpp parsemd.cpp -o crawler

The program will be named crawler. To run it, do:

./crawler crawlerConfig.txt

At the moment, the input file being used is data/index.txt.
The crawler is outputting into a file called crawled.txt in the data folder


To compile the Qt program, do:

qmake
make

To run the program, you will run:

./search searchConfig.txt

searchConfig.txt has crawled.txt as the input file by default.


A note about my Qt program that might not be obvious:
The sorting options in the main window carry over when you click on a webpage.
The exception is for the PageRank sort, where it defaults to sorting by filename.


Thanks, and have a nice day.

-Erick

