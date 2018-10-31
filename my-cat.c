/* 
my-cat utility
reads the given file and prints the output to the stdout-stream 
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	char buffer[250];
	
	if (argc == 1) //no command line parameters
		return 0;
	
	for (int i=1; i<argc; i++){ //go through all command line parameters except the first one
		FILE *file;
		file = fopen(argv[i], "r");
		if (!file){
			printf("my-cat: cannot open file\n");
			return 1;
		}
		while (fgets(buffer, 249, file)) //read line from file and print it
			printf("%s", buffer);
		
		fclose(file);
	}
	return 0;
}
