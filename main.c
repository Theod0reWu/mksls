#include "ls.h"

int main(int argc, char *argv[]) {
	printf("Listing all files in current directory\n");
	file_dlist(".");
	printf("size of current directory: %i\n", getdsize("."));
	printf("\nMy own personal ls -l function on the directory given in the command line ...\n");
	char name [256];
	//printf("%i\n", errno);
	if (argc < 2){
		printf("Enter the directory you want to look at please: ");
		fgets(name, 256, stdin);
		//name[strlen(name)-1] = 0;
		//printf("%i\n", errno);
		//printf("%s\n", strerror(errno));
		//printf("entered info|%s|\n", name);
		*strchr(name, '\n') = '\0';
	}else{
		//printf("%s\n", argv[1]);
		strcpy(name, argv[1]);
	}
	//name[strlen(name)-1] = '\0';
	ls_l(name);
	return 0;
}
