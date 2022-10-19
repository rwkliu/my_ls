//My version of the ls command with -a and -t options
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

#ifndef STRUCT_DIRENT_ARRAY
#define STRUCT_DIRENT_ARRAY
typedef struct s_dirent_array {
  int size;
  char **array;
} dirent_array;
#endif

int main(int argc, char *argv[]) {
  DIR *folder = NULL;
  int aflag = 0;
  int tflag = 0;
  struct dirent *entry;
  // struct stat filestat;
  
  printf("%d\n", argc);
  for(int i = 1; i < argc; i++) {
    if(strcmp(argv[i], "-a") == 0) {
      aflag = 1;
    }
    else if(strcmp(argv[i], "-t") == 0) {
      tflag = 1;
    }
    else if(strcmp(argv[i], "-at") == 0 || strcmp(argv[i], "-ta") == 0) {
      aflag = 1; 
      tflag = 1;
    }
    else {
      folder = opendir(argv[i]);
      if(folder == NULL) {
        printf("Unable to open directory\n");
        return 1;
      }
      printf("folder set to %s\n", argv[i]);
    }
    printf("a: %d\n", aflag);
    printf("t: %d\n", tflag);
  }

  if(argc == 1) {
    printf("%d\n", argc);
    folder = opendir(".");
  }

  if(folder == NULL) {
    folder = opendir(".");
    printf("Folder set to current directory\n");
    printf("Directory is opened!\n");
  }
  else {
    entry = readdir(folder);
    printf("Directory is opened!\n");
  }

  return 0;
}