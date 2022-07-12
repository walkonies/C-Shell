#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{

	// Declare variables
	char cmd[20][20];
	int pid;
	int i;

	// Copy arguments 
	if (argc >= 2){
		for (i = 1 ; i < argc ; i++){
			strcpy(cmd[i-1], argv[i]);
		}
	}

	// Fork
	switch(pid = fork()) {
		case -1: 
			perror("fork failed");
			break;
		// Child process
		case 0:
			// Execute function
			execvp(cmd[0], argv+1);
			perror("exec failed");
			break;
		// Parent process
		default: // parent uses wait to suspend execution until child finishes
			wait((int *)0);
			exit(0);
		}
	
 
	return 0;
}