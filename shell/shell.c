#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "mytoc.h"
#include "strcopy.h"
#include <sys/stat.h>
#include <sys/wait.h>   
int exiit,pid,execV,newP;
int numWords;
char input[1024];


char* getPDir(char *cwd){
  char* prevDir =(char*)malloc(100);
  prevDir="/";
  char **direct =mytoc(cwd,'/');
  
  for(int i =0;*direct[i]!='\0';i++){
    if(*direct[i+1]=='\0'){
	return prevDir;
      }
      prevDir=strcat(prevDir,direct[i]);
      prevDir=strcat(prevDir,"/");
  }
}

char * getPath(char **envp){
  for(int i=0; envp[i] != (char*)0;i++){ 
    char ** envPath =mytoc (envp[i],'=');
    if(checkPath(envPath[0])==1){
      return envPath[1];
    }
  }
  return NULL;
}

void changeDir(char** tokenV, char * cdw){
  struct stat sb;
  int req =0;
  if(tokenV[1]){
      req=checkDots(tokenV[1]);
    }
  if(*tokenV[1]!='\0' && (req==1)){
    char* previousDir= (char*)malloc(1024);
    previousDir = getPDir(cdw);
    chdir(previousDir);
    printf("%s\n",previousDir);
	
  }
  else{
    
    if(stat(tokenV[1], &sb)==0 && S_ISDIR(sb.st_mode)){
      chdir(tokenV[1]);
    }else{
      printf("bash: cd: ",tokenV[1]," :Not a directory\n");
    }
  }
}

int createChildProcess(char *path, char **tokenVect, char **eenvp,int ifCh){
  int exitNorm;
  pid = fork();
  if(pid == 0){
    execve(path,tokenVect,eenvp);
      
  }
  else if(pid <0){
    wait(&exitNorm);
    if(WIFSIGNALED(exitNorm)){
      printf("Program Terminated with exit code : %d\n",WTERMSIG(exitNorm));
    }
  }
  else{
    int waitVal, waitStatus, cStatus;
    char bu[100];
    waitVal=waitpid(-1,&waitStatus,WNOHANG);
    if(ifCh ==1){
      return 1;
    }
  }
    return 0;
}

void checkForCmd(char ** tokenV,char **ennvp,char **pathV){
  if(access(tokenV[0],F_OK)!=-1){
    createChildProcess(tokenV[0],tokenV,ennvp,0);
  }
  else{
    for(int i=0;pathV[i] != (char*)0;i++){	
      char *temp =strcat(pathV[i],"/");
      char *fullPath = strcat(temp,tokenV[0]);
      
      if(access(fullPath,F_OK)!=-1){
	createChildProcess(fullPath, tokenV,ennvp,0);
      }
    }	
  }//else
}//void

void pipesM(char ** pipeVect,char **envvp ,char ** tokenV,char **pathV){
  int exitNorm;
  struct stat sb;
  int fileDescriptor[2];
  char **pCmd1 = mytoc(pipeVect[0],' ');
  char **pCmd2 = mytoc(pipeVect[1],' ');

  if(stat(tokenV[0], &sb)==0){
    pipe(fileDescriptor);
    int pid = fork();

    if(pid==0){
      dup2(fileDescriptor[1],1);
      close(fileDescriptor[0]);
      execve(pCmd1[0],pCmd1,envvp);

    }
   else if(pid<0){
     wait(&exitNorm);
     if(WIFSIGNALED(exitNorm)){
       printf("Program Terminated with exit code : %d\n",WTERMSIG(exitNorm));
     }

   }//<0
   else{
     int waitVal, waitStatus;
     int childStatus;

     close(fileDescriptor[1]);
     waitVal = waitpid(pid, &waitStatus,0);
     pid = fork();
     if(pid ==0){
       dup2(fileDescriptor[0],0);
       close(fileDescriptor[1]);
       execve(pCmd2[0],pCmd2,envvp);
     }
     
     else if(pid<0){
       wait(&exitNorm);
       if(WIFSIGNALED(exitNorm)){
	 printf("Program Terminated with exit code : %d\n",WTERMSIG(exitNorm));
       }
     }//adopted child <0
     else{
       dup2(1,fileDescriptor[1]);
       dup2(0,fileDescriptor[0]);
       waitVal = waitpid(pid,&waitStatus,0);


     }//child else

   }//parent else
    
  }//if stat tokenV, path givven
  else{
    int fd[2];
    
    for(int i=0;pathV[i] != (char*)0;i++){	
      char *temp =strcat(pathV[i],"/");
      char *fullPath = strcat(temp,pCmd1[0]);
      if(stat(fullPath, &sb)==0){
	int pid2 = fork();

	if(pid2 ==0){
	  dup2(fd[1],1);
	  close(fd[0]);
	  execve(fullPath,pCmd1,envvp);
	}//if 0
	else if(pid2 <0){
	  wait(&exitNorm);
	  if(WIFSIGNALED(exitNorm)){
	    printf("Program Terminated with exit code : %d\n",WTERMSIG(exitNorm));
	  }//signal if
	}//<0
	else{
	  int waitVal1,waitStatus1;
	  int childStatus;
	  close(fd[1]);
	  waitVal1=waitpid(pid2,&waitStatus1,0);
	  
	  
	  for(int j=0;pathV[j] != (char*)0;j++){	
	    char *temp2 =strcat(pathV[j],"/");
	      char *fullPath2 = strcat(temp,pCmd2[0]);
	      if(stat(fullPath2,&sb)==0){
		int pid3=fork();
		if(pid3 ==0){
		  dup2(fd[0],0);
		  close(fd[1]);
		  execve(fullPath2,pCmd2,envvp);
		  
		}//if ==0
		else if(pid3 <0){
		  wait(&exitNorm);
		  if(WIFSIGNALED(exitNorm)){
		    printf("Program Terminated with exit code : %d\n",WTERMSIG(exitNorm));
		  }//signal if
		}//<0
		
		else{
		  int waitVal2, waitStatus2;
		  dup2(1,fd[1]);
		  dup2(0,fd[0]);
		  waitVal2=waitpid(pid2,&waitStatus2,0);
		  
		  
		}//else of child
	      }//if stat blah
	      
	    }//yet another for
	  }//another else ;_; parent else
			 
      }//if path found
      

    }//for path given loop

  }//else path not given
  

}//mehod bracket

int main (int arc, char **arg, char **envp){
  char * PS1 = getenv("PS1");
  char **tokenVector;
  char **pathVector;
  char **pipesVector;
  char *path;
  char **vectorForPipes;
  char **backgroundP;
  int done,numTok =0;

  struct stat st;
  
  while(exiit!=1){
    char *cmd =NULL;
    char *cwd =NULL;
    char * PS1 = getenv("PS1");
    
    write (1,"[os shell]$ ",12);
    int numBytesRead = read(0,input,sizeof(input));
    input[numBytesRead-1]='\0';
    exiit = checkEx(input);
    if(input[0]=='\0'){
      exit(0);
    }
    path = getenv("PATH");
    tokenVector = mytoc(input,' ');
    numTok =numWords;
   
    pipesVector = mytoc(input,'|');
    cmd=tokenVector[0];
    cwd =getcwd(cwd,1000);

    pathVector =mytoc(path,':');
    
    vectorForPipes =mytoc(input,'&');
    
    if(vectorForPipes[1]){
      backgroundP=mytoc(tokenVector[0],' ');
      
      if(stat(backgroundP[0], &st)==0){
	done =1;
	int chekp =createChildProcess(backgroundP[0],vectorForPipes,envp,1);
	if(chekp ==1)return 1;
      }//if access
      
    else{
      for(int i=0;pathVector[i] != (char*)0;i++){	
        char *temp =strcat(pathVector[i],"/");
	char *trimmed = trim(backgroundP[0],' ');
	char *fullPath = strcat(temp, trimmed);
	printf("%s\n",fullPath);
	
	if(stat(fullPath,&st)==0){
	  done =1;
	  createChildProcess(fullPath,vectorForPipes,envp,0);
	} //if access full path
      }//f pr loop
     }//e;se
    }//background if
    if(checkCd(tokenVector[0])==1){
      done =1;
      changeDir(tokenVector,cwd);
    }
    if (tokenVector[0]){
      done =1;
      checkForCmd(tokenVector,envp,pathVector);
    }
    if(pipesVector[1]){
      done =1;
      pipesM(pipesVector,envp,tokenVector,pathVector);
    }//pipes first if
    if(exiit !=1){
    if (done != 0){
      printf("bash command not found :%s\n ", tokenVector[0]);
    }//not found command if
    }//not found command exit
    
    for(int i =0;i<sizeof(input);i++){
      input[i]='\0';

    }
  }//exit while
  return 1;
}
 

