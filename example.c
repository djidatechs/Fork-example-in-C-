#include <stdio.h>
#include <unistd.h>
int main(int argc, char  *argv[])
{

	printf("THIS LINE IS FIRED FROM %s",argv[0]);
	puts(".c\n");
}