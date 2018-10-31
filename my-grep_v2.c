/* 
my-grep utility
looks through a file, trying to find a user-specified search term in the line
*/

#include <stdio.h>
#include <stdlib.h>

struct data{
	int character;
	struct data *pNext;
};

int main(int argc, char* argv[]){
	
	int search_success = 0;
	int j = 0;
	int temp;
	char buffer[250];
	FILE* file;
	struct data *pAlku = NULL, *pLoppu = NULL, *ptr;
	
	if (argc == 1){ //no command-line arguments
		printf("my-grep: searchterm [file ...]\n");
		exit(1);
	}else if (argc == 2){ //read from standard input
		int x = 0, y = 0;
		fgets(buffer, 249, stdin);
		while (buffer[x] != '\0'){ //check line for user term
			if (buffer[x] == argv[1][y])
				y++;
			else
				y = 0;
			x++;
			if (argv[1][y] == '\0'){
				search_success = 1;
				break;
			}
		}
		if (search_success) //print line if user term is found
			printf("%s", buffer);
	}else{
		for (int i=2; i<argc; i++){ //go through all command line parameters except the first two
			file = fopen(argv[i], "r");
			if (!file){
				printf("my-grep: cannot open file\n");
				exit(1);
			}
			while ((temp = fgetc(file)) != EOF){ //take one character from file
				if(!(ptr = malloc(sizeof(struct data)))){
					perror("malloc fault");
					exit(1);
				}
				(*ptr).character = temp; //put character inside linked list
				(*ptr).pNext = NULL;

				if (pAlku == NULL){
					pAlku = ptr;
					pLoppu = ptr;
				}else{
					(*pLoppu).pNext = ptr;
					pLoppu = ptr;
				}
				if (temp == '\n'){ //if character is new line then...
					search_success = 0;
					ptr = pAlku;
					j = 0;
					while (ptr){ //check linked list (line) for user term
						if ((*ptr).character == argv[1][j])
							j++;
						else
							j = 0;
						ptr = (*ptr).pNext;
						if (argv[1][j] == '\0'){
							search_success = 1;
							break;
						}
					}
					if (search_success){ //print linked list (line) if user term is found
						ptr = pAlku;
						while(ptr){
							printf("%c", (*ptr).character);
							ptr = (*ptr).pNext;
						}
					}
					pLoppu = pAlku; //free linked list
					while(pLoppu){
						pAlku = (*pLoppu).pNext;
						free(pLoppu);
						pLoppu = pAlku;
					}
				}
			}
		}
	}
	return 0;
}
/* eof */
