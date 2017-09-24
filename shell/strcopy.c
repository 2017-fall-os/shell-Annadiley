#include "strcopy.h" 		/* for consistency */
#include <stdlib.h>		/* for malloc */

char *strcopy(char *inStr, int current)	/* like strdup */
{
  char *pStr, *copy, *pCopy;
  size_t len;
    for (pStr = inStr; *pStr; pStr++)            // count # chars in str
      ;
    len = pStr - inStr + 1;
 
  if(current!=0){
    for(int i=0;i<current;i++){
      copy = pCopy = (char *)malloc(current);    // allocate memory to hold  copy 
  
      for (pStr = inStr; *pStr; pStr++)          // duplicate 
	*(pCopy++) = *pStr;
    }
  }
  else{
    copy = pCopy = (char *)malloc(len);         // allocate memory to hold  copy 
       for (pStr = inStr; *pStr; pStr++)        // duplicate 
	*(pCopy++) = *pStr;
  }
  *pCopy = 0;		      	                // terminate copy 
  return copy;
}
int getLeenght(char *str){                      //gets lenght of given string
  int len=0;
  for(char *pStr =str;*pStr;pStr++){
    len++;
  }
  return len;
  
}
char *strcat(char *str, char *secStr){          //concatinates two given strings
  char *newStr, *pNewStr;
  int leng1= getLeenght(str);                   //gets lenght of the two strings
  int leng2= getLeenght(secStr);
  newStr = pNewStr= (char*)malloc((size_t)leng1+leng2+1);   //alocates memory for them
 
  for(int i =0;i<leng1;i++){                                //add the complete first string to the new one
    *pNewStr =*(str+i);                                      
    pNewStr++;
  }
  for(int j=0; j<leng2;j++){                                //at the end of the first one, add the second string
    *pNewStr=*(secStr+j);
    pNewStr++;
  }
  *pNewStr=0;                                                //terminate copy
  return newStr;

}
