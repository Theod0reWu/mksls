#include "ls.h"

int main(int argc, char const *argv[]) {
	printf("Listing all files in current directory\n");
	file_dlist(".");
	printf("size of current directory (including subdirectories): %i\n", getdsize("."));
	printf("\nMy own personal ls -l function...\n");
	ls_l(".");
	return 0;
}