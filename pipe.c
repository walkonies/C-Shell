#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	// Declare variables
	int fd[2];
	int pid;

	// Create pipe
	pipe(fd);

	// Fork
	pid = fork();

	// Error check
	if (pid<0){
		printf("ERROR!\n");
	}
	// child process
	else if (pid == 0){
		// Close input and change to pipe
		close(0);
		dup(fd[0]);
		close(fd[0]);
		close(fd[1]);

		// Exe command
		execvp("./sort", NULL);
	}
	// parent process
	else{
		// Close output and change to pipe
		close(1);
		dup(fd[1]);
		close(fd[1]);
		close(fd[0]);

		// Exe command
		execvp("./pre", NULL);

		exit(1);
	}
	return 0;
}