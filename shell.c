/*			Lab 2 COMPLETE			*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	char *path, *argv[20], buf[80], n, *p;
	int m, status, inword, continu;

	while(1) {
		inword = 0;
		p = buf;
		m = 0;
		continu=0;

		printf( "\nshhh> ");

		while ( ( n = getchar() ) != '\n'  || continu ) {

			if ( n ==  ' ' ) { 

	    		if ( inword ) {

					inword = 0;

					*p++ = 0;
				} 
			}
			else if ( n == '\n' ) continu = 0;
			else if ( n == '\\' && !inword ) continu = 1;
			else {
				if ( !inword ) {
					inword = 1;
					argv[m++] = p;
					 *p++ = n;
					}
				else 
					*p++ = n;
			}
		}

		*p++ = 0;
		argv[m] = 0; 

		int i;
		int pipes = 0;

		int inFlag = 0;
		int outFlag = 0;
		char inFile[30];
		char outFile[30];

		int pid;
		int left_fd[2];
		int right_fd[2];

		int k[m];
		int size = 1;
		k[0] = 0;

		// exit
		if ( strcmp(argv[0],"exit") == 0 ) exit (0);

		// Preprocessing check
		for (i = 0 ; i < m ; i++){
			// check for pipes
			if (strcmp(argv[i], "|") == 0){
				argv[i] = 0;
				pipes++;
				k[size] = i+1;
				size++;
				//printf("pipe\n");
			}
			// check for input
			else if (strcmp(argv[i], "<") == 0){
				argv[i] = 0;
				inFlag = 1;
				strcpy(inFile, argv[i+1]);
				//printf("input %s\n", inFile);
			}
			// check for output
			else if (strcmp(argv[i], ">") == 0){
				argv[i] = 0;
				outFlag = 1;
				strcpy(outFile, argv[i+1]);
				//printf("output %s\n", outFile);
			}
		}

		for (i = 0; i <= pipes; i++){
    		// there are pipe and not last process
    		if (pipes > 0 && i != pipes){
    			// create right pipe
    			pipe(right_fd);
    		}

    		// fork
    		pid = fork();

    		//error
    		if (pid < 0){printf("ERROR");}

    		// parent process
    		else if (pid > 0){
    			if (i > 0) {
    				close(left_fd[0]);
    				close(left_fd[1]);
    			}
    			left_fd[0] = right_fd[0];
    			left_fd[1] = right_fd[1];
    			wait(0);
    		}

    		// child process
    		else{
    			// input redirection and first process
    			if (inFlag && i == 0){
    				// deal with input redirection
    				int n=open(inFile, O_RDONLY);
    				close(0);
    				dup(n);
    				close(n);
    			}
    			// there are pipes
    			if (pipes > 0){
    					//1st process
    					if (i==0){ 
    						// change output to right pipe
    						close(1);
    						dup(right_fd[1]);
    						close(right_fd[1]);
    						close(right_fd[0]);
    					}
    					//last process
    					else if (i == pipes){ 
    						// change input to left pipe
    						close(0);
    						dup(left_fd[0]);
    						close(left_fd[0]);
    						close(left_fd[1]);
    					}
    					//middle process
    					else {
    						// change output to right pipe and input to left pipe
    						close(1);
    						dup(right_fd[1]);
    						close(right_fd[1]);
    						close(right_fd[0]);
    						close(0);
    						dup(left_fd[0]);
    						close(left_fd[0]);
    						close(left_fd[1]);
    					}
    				}
    			//there is output redirection && this is the last process
    			if (outFlag && i == pipes){ 
    				// deal with output redirection
    				int n = creat(outFile,0750);
    				close(1);
    				dup(n);
    				close(n);
    			}

    			// exec
    			execvp(argv[k[i]], &argv[k[i]]);
    		}
    		
    	} // end of for loop
    }
}


