#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "mytoc.h"
#include "strcopy.h"
#include <sys/stat.h>
#include <sys/wait.h>
//function declarations
void createChildProcess(char * path , char **tokenVect, char **eenvp);
   
int equalsExit,pid,execV;
char stri[1000];
char *toExecute;
int main (int atgc, char **arg, char **envp){
  char *enpath;
  while(equalsExit!=1){
    write(1,"$ ",2);                            //display the $ promt
    int bytesRead=read(1,stri,sizeof( stri));                 //get user input
    stri[sizeof(char)*bytesRead-1]='\0';
    char **tokeenVect =mytoc(stri,' ');         //call my tokenizer function
    equalsExit =checkEx(stri);
    int ac =0;
    if(tokeenVect[0]){                          //if vector is not empty start command    
      for(int i=0;envp[i] != (char *)0;i++){        //as long as the envp contains no 0
	 char ** envPath =mytoc (envp[i],'=');       //tokenize path
	 if(checkPath(envPath[0])){                  //check if word path was found
           enpath= envPath[1];                       //return env, which should be in next potition on array
           break;
	 }
      }
      char **pathVect = mytoc(enpath,':');          //tokenize path from envp variable
      if(access(tokeenVect[0],F_OK)!=-1){          //If it is a full path
	printf("Excecuting command:\n", tokeenVect[0]);
	createChildProcess(tokeenVect[0] ,tokeenVect, envp); //create process
	}
      else {                                                  //search for full path
	for( int i=0;pathVect[i] !=(char*)0;i++){
	  char *temp = strcat(pathVect[i],"/");
	  char *fullPath =strcat(temp,tokeenVect[0]);
	  if(access(fullPath,F_OK)!=-1){
	    ac=1;
	    createChildProcess(fullPath ,tokeenVect, envp); //create process
	    break;  
	  }
	}
	if(!equalsExit&&ac==0){
	printf("Command not found\n");
	}
     }
    for(int i =0; i<sizeof(stri);i++){     //free previous space
      stri[i]='\0';
    }
    }
  }return 0;
}
 void createChildProcess(char * path , char **tokenVect, char **eenvp){
   int exitNorm;                          //used to check if child process terminated normaly
   // fflush(NULL);
   pid = fork();                          //create child process
   if(pid == 0){                          
     execve(path,tokenVect,eenvp);        //execute child process
     
   }
   else if (pid <0){ 
     wait(&exitNorm);                                 //checks if process terminated abnormally
     if(WIFSIGNALED(exitNorm)){
       printf("Program Terminated with exit code : %d\n",WTERMSIG(exitNorm));
     }

   }

 }
 

