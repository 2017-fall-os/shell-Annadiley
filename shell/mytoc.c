#include "mytoc.h"
#include <stdio.h>
#include <stdlib.h>
#include "strcopy.h"
int equalsExit,numWords,currentWordLen;
char *stricopy;                               
int len[100];                              //stores lenght of every word
char checkPath(char *str){
   while(*str != '\0'){
    if(*str =='P'){
	*str ++;
	if(*str =='A'){
	  *str++;
	  if(*str =='T'){
	    *str++;
	    if(*str =='H'){
	      return 1;
	    }
	  }
	}
      }
    *str++;
   }
  return 0;
}

int checkEx(char *str){
  while(*str != '\0'){
    if(*str =='e'){
	*str ++;
	if(*str =='x'){
	  *str++;
	  if(*str =='i'){
	    *str++;
	    if(*str =='t'){
	      return 1;
	    }
	  }
	}
      }
    *str++;
  }
  return 0;
}

void countWords(char *str, char delim){    //get the number of words in the string
  numWords = currentWordLen =0;
  if(*str !='\0'){
    numWords=1;               //if string is not empty, it contains a word
    while(*str != '\0'){      //as long as we are not at the end of the string
      currentWordLen++;       //if a char is found increase lenght of word
      if(*str == delim){
	len[numWords]=currentWordLen-1; //at the current word add the lenght
	                                //substract one because of the space
	numWords++;                     //increase the number of found words
	currentWordLen=0;               //set the current word lenght to 0
      }
     *str++;                   //advance the pointer to next character
    }
    len[numWords]=currentWordLen;       //add lenght to final word
  }
 
}

char ** mytoc(char *str,char delim){
 
  stricopy =strcopy(str,0);

  countWords(stricopy,delim);                      //gets number of words and lenght of words

  char ** tokenVec = (char **) calloc((numWords+1), sizeof(char*));               //allocates memory for vector given the amount of words

  for(int tokNum=1;tokNum <= numWords;tokNum++){      // for each word
    tokenVec[tokNum-1]=(char*)malloc(len[tokNum+1]);  //allocate space for the word
    char* a =(char*)malloc(len[tokNum+1]+1);          //allocate memory for the string word
    a =strcopy(str,len[tokNum]);                      //copy only the desired word, using the lenght as a reference of when to stop into a new string
    a[len[tokNum]]='\0';                              //add terminating symbol at the final position of the string
    for(int i=1; i<=len[tokNum]+1;i++){              //advance the current pointer to the next word
      str++;
    }
    tokenVec[tokNum-1]=a;                            //add the complete word to the vector
  }
  tokenVec[numWords+1]='\0';                         //add terminating symbol at the end of vector
  return tokenVec;                                   //return the vector
}
