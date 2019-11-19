
#include "ls.h"

/*
-list all the files in the directory
specify which files are directories (if any)
show the total size of all the regular files the directory
note that you do not have to recursively go through any subdirectories to find their size for this part (unless you want to, but that is not a simple task)
Have the program scan the current directory
Possible enhancements:
Recursively list the files in any subdirectories, update the total to include the total size of subdirectories
Print out the size in a more readable format (like using KB, MB, GB for -byte prefixes)
Make it look more like $ ls -l
*/

void file_list(){
  DIR * this_dir = opendir(".");
  if (this_dir == NULL) {
    printf("Could not open current directory" );
    return;
  }
  struct dirent * de = readdir(this_dir);
  while (de != NULL){
    printf("%s\n", de->d_name);
    de = readdir(this_dir);
  }
  closedir(this_dir);
}

void file_dlist(char * path){
  printf("for the directory: %s\n", path);
  DIR * this_dir = opendir(path);
  if (this_dir == NULL) {
    printf("Could not open the directory: %s", path );
    return;
  }
  struct dirent * de = readdir(this_dir);
  char * name;
  struct stat st;
  printf("Directories: \n");
  int f = 1;
  while (de != NULL){
    name =  de->d_name;
    stat(name, &st);
    if (f && !S_ISDIR(st.st_mode)){
      printf("Regular Files:\n");
      f = 0;
    }
    if (S_ISDIR(st.st_mode)){
      printf("  %s \n", name);
    }
    else {
      printf("  %s\n", name);
    }
    de = readdir(this_dir);
  }
  closedir(this_dir);
}

int getdsize(char * path){
  int size = 0;
  DIR * this_dir = opendir(path);
  if (this_dir == NULL) {
    //printf("Could not open the directory: %s \n", path );
    return 0;
  }
  struct dirent * de = readdir(this_dir);
  char * name;
  struct stat st;
  while (de != NULL){
    name = de->d_name;
    stat(name, &st);
    if (strcmp(name, ".") != 0 && strcmp(name, "..") != 0){
      if(S_ISDIR(st.st_mode)){
        //printf("%s\n", name);
        //size += getdsize(name);
      }
      size += st.st_size;
    }
    de = readdir(this_dir);
  }
  closedir(this_dir);
  return size;
}

void ls_l(char * path){
  DIR * this_dir = opendir(path);
  if (this_dir == NULL || errno) {
    printf("Could not open the directory: %s \n", path );
    printf("%s\n", strerror(errno));
    return;
  }
  struct dirent * de = readdir(this_dir);
  char * name;
  struct stat st;
  char * stuff;
  while (de != NULL){
    name = de->d_name;
    stat(name, &st);
    if (strcmp(name, ".") != 0 && strcmp(name, "..") != 0){
      stuff = get_info(st);
      printf("%s %s\n", stuff, name);
      free(stuff);
    }
    de = readdir(this_dir);
  }
  closedir(this_dir);
}

char * get_info(struct stat st){
  char * str = calloc(300,sizeof(char));
  int len = 1;
  if (S_ISDIR(st.st_mode)){str[0] = 'd';}
  else {str[0] = '-';}
  //printf("%s\n", str);
  //extract permissions from last 8 bits of mode
  int mode = st.st_mode & (int) pow(2,9)-1;
  int smode [3]; int i = 2;
  while (mode > 0){
    smode[i] = mode % 8;
    mode = mode / 8;
    i--;
  }
  //printf("%i\n", smode[0]);
  for (i = 0; i < 3; i++){
    for (int p = 0; p < 3; ++p){
      //printf("P's %i : %i \n", p, smode[i]);
      //printf("%s : %i\n",str, len );
      if (p == 0 && smode[i] % 2 == 1){str[len] = 'r' ;}
      else if (p == 1 && smode[i]  % 2 == 1) {str[len]= 'w';}
      else if (p == 2 && smode[i]  % 2 == 1) {str[len] = 'x';}
      else {str[len] = '-';}
      smode[i] = smode[i] / 2;
      ++len;
    }
  }
  str[len++] = ' ';
  str[len++] = '0' + st.st_nlink;
  str[len++] = ' ';
  char * usr_name = getpwuid(st.st_uid)->pw_name;
  strcpy(str+len, usr_name);
  len += strlen(usr_name);
  str[len++] = ' ';
  for (int n = st.st_uid; n > 0; n /= 10){
    str[len++] = '0' + n % 10;
  }
  str[len++] = ' ';
  //printf("%i\n", st.st_size);
  for (int n = st.st_size; n > 0; n /= 10){
    str[len++] = '0' + n % 10;
  }
  if (st.st_size == 0){
    str[len++] = '0';
  }
  str[len++] = ' ';
  strncpy(str+len,ctime(&st.st_atime)+4, 12);
  len+=12;

  //printf("%s : %i\n", str, len);
  str[len++] = '\0';
  return str;
}