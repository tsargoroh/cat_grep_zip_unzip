/*
my-grep utility
looks through a file, trying to find a user-specified search term in the line
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	char *line = NULL, *tmp;
	size_t size = 0;
	
	if (argc == 1){ //no command-line arguments
		printf("my-grep: searchterm [file ...]\n");
		return 1;
	}
	if (argc == 2){ //read from standard input
		getline(&line, &size, stdin);
		tmp = strstr(line, argv[1]);
			if (tmp)
				printf("%s", line);
	}
	
	for (int i=2; i<argc; i++){ //go through all command line parameters except the first two
		FILE *file;
		file = fopen(argv[i], "r");
		if (!file){
			printf("my-grep: cannot open file\n");
			return 1;
		}
		
		while (getline(&line, &size, file) != -1){ //search user term in a line and print it if found
			tmp = strstr(line, argv[1]);
			if (tmp)
				printf("%s", line);
		}
		fclose(file);	
	}
	return 0;
}
