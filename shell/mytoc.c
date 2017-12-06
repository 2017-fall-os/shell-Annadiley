#include "mytoc.h"
#include <stdio.h>
#include <stdlib.h>
#include "strcopy.h"
int equalsExit,numWords,currentWordLen;
char *stricopy;                               
int len[1024];
int checkDots(char *str){
  while(*str != '\0'){
    if(*str =='.'){
      if(*str =='.'){
	return 1;
      }
    }
    *str++;
  }
  return 0;
}
int checkPath(char *str){                 //Checks if the given string contains the word path on it
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

int checkEx(char *str){                     //checks if th given string contains the word exit
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
int checkCd(char *str){
  while(*str != '\0'){
    if(*str =='c'){
	*str ++;
	if(*str =='d'){
	  return 1;
	}
    }
    *str++;
  }
  return 0;
}
void countWords(char *str, char delim){    //get the number of words in the string
  numWords = currentWordLen =0;
  if(*str ==' '){
    
  }
  else if(*str !='\0'){
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
char * trim(char *str, char delim){
  while(*str == delim){
    str++;
  }
  return str;
}

char ** mytoc(char *str,char delim){
 
  stricopy =strcopy(str,0);

  countWords(stricopy,delim);

  char ** tokenVec = (char **) calloc((numWords+1), sizeof(char*));           
  for(int tokNum=1;tokNum <= numWords;tokNum++){      
    tokenVec[tokNum-1]=(char*)malloc(len[tokNum+1]);
    char* a =(char*)malloc(len[tokNum+1]+1);
    a =strcopy(str,len[tokNum]);            
    a[len[tokNum]]='\0';                   
    for(int i=1; i<=len[tokNum]+1;i++){    
      str++;
    }
    trim(a,' ');
    tokenVec[tokNum-1]=a;
  }
  tokenVec[numWords+1]='\0';              
  return tokenVec;                        
}
