#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "mytoc.h"
#include "strcopy.h"
#include <sys/stat.h>
int equalsExit,pid,execV;
char stri[1000];
int main (int atgc, char **arg, char **envp){
  char *enpath;
  for(int i=0;envp[i] != (char *)0;i++){ //as long as the envp contains no 0
    char ** envPath =mytoc (envp[i],'=');   //tokenize path
    if(checkPath(envPath[0])){           //check if word path was found
      enpath= envPath[1];                //return env, which should be in next potition on array
      break;
    }
  }
  char **pathVect = mytoc(enpath,':');   //tokenize path from envp variable
  
  
  while(equalsExit!=1){
    write(1,"$0",1);                      //display the $ promt
    read(1,stri,sizeof( stri));           //get user input
    stri[sizeof(stri)+1]='\0';
    char **tokeenVect =mytoc(stri,' ');   //call my tokenizer function
    equalsExit =checkEx(stri);            //check if there must be an exit of the loop

    if(tokeenVect[0]){                    //if vector is not empty start command
      





      /*   pid = fork();                       //create process to start command
      if(pid==0){
	execV=execve(tokeenVect[0],tokeenVect,envp);
      }
      else if(

      
      }*/
    }
     for(int i =0; i<sizeof(stri);i++){     //free previous space
      stri[i]='\0';
    }                   
  } return 0;
}
