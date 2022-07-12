
#include <stdio.h>
#include <string.h>


int main(int argc, char const *argv[])
{
	// Declare students array and input variables
	int n = 32;
	char words[n][n];
	int size = 0;
	char input[n];

	// Get user input
	while((scanf("%s", input))!= EOF){
		strcpy(words[size], input);

		// Incriment size
		size++;
		if (size >= n){
			break;
		}
	}

	// Bubble sort
	char temp[30];
	int i, j;
	for(i=0; i<size; i++){
    	for(j=0; j<size-1-i; j++){
      		if(strcmp(words[j], words[j+1]) > 0){
        	//swap words[j] and words[j+1]
        		strcpy(temp, words[j]);
        		strcpy(words[j], words[j+1]);
        		strcpy(words[j+1], temp);
        	}
        }

    }

    // Output sorted array
    for (i = 0 ; i < size ; i++){
		printf("%s\n", words[i]);
	}

	return 0;
}