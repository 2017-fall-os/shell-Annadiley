## Directory
This program contains the following files:
-mytoc.h - contains the tokenizer's header
-mytoc.c - main file for the tokenizer
-strcopy.h - header for the strcopy file
-strcopy.c - contains several help functions as str concatination and copy
-shell.c - main program, contains main and is in charge of forking and executing

## How to Run
-To create files, once in the directory type "make"
-To run the tokenizer type "make run"
-To clean *.o files, type "make clean"

## Extra Notes and Credits
-On the file shell.c, the function isExecutable was made based on what can be found on: https://stackoverflow.com/questions/13098620/using-stat-to-check-if-a-file-is-executable-in-c

-The usage of wait() and WIFSIGNALED in the function isExecutable was based on how it was used on : https://hackintoshrao.com/tag/wifexited-and-wifsignaled-macros/
