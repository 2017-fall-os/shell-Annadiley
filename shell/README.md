## Directory
This program contains the following files:
-mytoc.h - contains the tokenizer's header
-mytoc.c - main file for the tokenizer
-strcopy.h - header for the strcopy file
-strcopy.c - contains several help functions as str concatination and copy
-shell.c - main program, contains main and is in charge of forking and executing

## How to Run
-To create files, once in the directory type "make"
-To run the tokenizer type "sudo make run" and type user password
-To clean *.o files, type "make clean"

## Extra Notes and Credits
-The usage of wait() and WIFSIGNALED in the function isExecutable was based on how it was used on : https://hackintoshrao.com/tag/wifexited-and-wifsignaled-macros/
-The usage of the stat(dirName,&sb)==0........
 line was based on the information found on : https://stackoverflow.com/questions/12510874/how-can-i-check-if-a-directory-exists
 ## Edit: 12/6/2017
 - Shell does not pass any of the test with testShell.sh, but it does work with direct input for some reason
 - The shell does accept basic command inputs however, it does not pass any test from the testShell
 - The shell does change directory without problem
 - There are a couple of bugs with piping and background process, but mostly it is now functional
