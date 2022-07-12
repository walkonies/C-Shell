#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	int pid, pid2;
	pid = fork();

	if (pid < 0){
		fprintf(stderr,"Fork failed\n");
	}
	else if (pid==0){
		pid2 = fork();

		if (pid2 < 0){
			fprintf(stderr,"Fork failed\n");
		}
		else if (pid2 == 0){
			execlp("/bin/pwd", "pwd", NULL);
		}
		else{
			wait(NULL);
			execlp("/bin/ls", "ls", NULL);
		}
	}
	else{
		wait(NULL);
		printf("Child complete\n");
	}
	return 0;
}

/*
alt using switch:
	// Fork
	switch(pid = fork()) {

		// Error check
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
*/