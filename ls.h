#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <string.h>
#include <errno.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#include <pwd.h>

#include <math.h>

void file_list();
void file_dlist(char * path);
int getdsize(char * path);
void ls_l(char * path);
char * get_info(struct stat st);