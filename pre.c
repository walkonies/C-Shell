#include <stdio.h>
#include <string.h>

struct Student{
	char name[20];
	float gpa;
};

int main(int argc, char const *argv[])
{
	
	// Declare students array and input variables
	int n = 32;
	int size = 0;
	struct Student students[n];
	char in_name[n];
	float in_gpa;

	// Get input while loop
	while(scanf("%s %f", in_name, &in_gpa)!=EOF){
		
			// Make student struct
		strcpy(students[size].name, in_name);
		students[size].gpa = in_gpa;

		// Incriment size
		size++;
		if (size >= n){
			printf("No more space!\n");
			break;
		}
	}

	// Iterate and print 3.0+ gpa
	int i;
	for (i = 0 ; i < size ; i++){
		if (students[i].gpa >= 3.0){
			printf("%s\n", students[i].name);
		}
	}
	return 0;
}
