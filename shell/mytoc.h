#ifndef mytoc_included
#define mytoc_included

// variables that will store the number of characters and spaces in a string
extern int numChar , numWords;

//Method get the lenght of the string
void countWords (char *str, char delim);

//Method used to check if there is the word path
int checkPath(char *str);
int checkDots(char *str);
int checkCd(char *str);
//Method to check if the command entered is to exit
int checkEx(char *str);
char *trim(char * str, char delim); 
//Main tokenizer method
char ** mytoc(char *str, char delim);
#endif
