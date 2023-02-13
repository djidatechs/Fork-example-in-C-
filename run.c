#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char  *argv[])
{
	if (argc !=  2 ) {
		printf("Please enter the right arguments\n"); 
		exit(EXIT_FAILURE);

	}	
	//get fileName from arguments
	char *fileName = argv[1];


	//affirm that the file is in fact a C file

	if (strlen(fileName) < 3) {
		printf("%s : is not a .c file\n",fileName);
		exit(EXIT_FAILURE);
	}

	char *dot = fileName[strlen(fileName)-2];
	char *extention = fileName[strlen(fileName)-1];
	
	//test is extention of fileName is .c
	if (strcmp (&dot , ".") || strcmp(&extention , "c")){
		printf("%s : is not a .c file\n",fileName);
		exit(EXIT_FAILURE);
	}
	//capture program.o and program in objectFile and outputFile
	char* objectFile = malloc(4);
	char* outputFile = malloc(4);
	strncpy(objectFile, fileName, strlen(fileName)-2);
	strncpy(outputFile, fileName, strlen(fileName)-2);
	
	strcat(objectFile,".o");
	//start creating the processes
	printf("Trying to excute this file : %s \n",fileName);
	int p1 ;
	int p2 ; 
	int status1 ;
	int status2 ;
	p1 = fork();
	
	if (p1<0) {
		printf("Failed to create a process\n");
		 exit( EXIT_FAILURE );
	}
	if (p1 == 0) {
		//compiling 
		char *binaryPath = "/bin/gcc";
  		char *arg1 = "-c";
  		char *arg2 = fileName;
  		char *arg3 = "-o";
  		char *arg4 = objectFile;
		printf("start compiling\n");
		execl(binaryPath, binaryPath, arg1,arg2,arg3,arg4, NULL);
		printf("Failed to compile the file\n");
		exit(EXIT_FAILURE);
	}
	else {
		//compiling is done 

		//link editing 
		waitpid(p1 , &status1 , 0);
		if (status1 >> 8 == 0){
			p2 = fork();
			if (p2 <0) {
				printf("Failed to create a process\n");
				exit( EXIT_FAILURE );
			}
			else if (p2 == 0) {
				char *binaryPath = "/bin/gcc";
		  		char *arg1 = objectFile;
		  		char *arg2 = "-o";
		  		char *arg3 = outputFile;
				printf("start linking\n");
				execl(binaryPath, binaryPath, arg1,arg2,arg3, NULL);
				printf("Link editing failed\n");
				exit(EXIT_FAILURE);
			}
			else{
				waitpid(p2 , &status2 , 0);
				if (status2 >> 8 == 0){
					//executing 
					char *binaryPath = outputFile;
					printf("executing ...\n");
					execl(binaryPath, binaryPath, NULL);
					printf("Executing failed\n");
					exit(EXIT_FAILURE);
				}
				else {
					printf("linking failed , Error status is: %i\n",status2);
					exit(EXIT_FAILURE);
				}
			}
	}
	else {
		printf("compiling failed , Error status is: %i\n",status1);
		exit(EXIT_FAILURE);
	}
	}

}