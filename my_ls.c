//My version of the ls command with -a and -t options
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include "dir_ops.h"

int main(int argc, char *argv[]) {
  int aflag = 0;
  int tflag = 0;
  int i = 0;
  int dir_ind = 0;
  int dir_size;
  int curr_opt;
  char *directory_name = NULL;
  char **directories = malloc(argc * sizeof(char *));
  char **head = directories;
  
  //Parse the optional arguments that start with '-'
  while((curr_opt = getopt(argc, argv, "at")) != -1) {
    switch(curr_opt){
      case 'a':
        aflag = 1;
        break;
      case 't':
        tflag = 1;
        break;
    }
  }

  //Parse the non-option arguments
  for(i = optind; i < argc; i++) {
    if(check_dir(argv[i]) == 1) {
      printf("Unable to open directory\n");
    }
    else {
      directories[dir_ind] = argv[i];
      dir_ind++;
    }
  }
  directories[dir_ind] = '\0';
  directories = realloc(directories, dir_ind);
  //If the first non-option argument is a valid directory, 
  //Print each directory's entries
  if(directories[0] != NULL) {
    directories = sort_dir_names(directories, dir_ind);
    dir_size = dir_ind;
    dir_ind = 0;
    while(*directories[dir_ind] != '\0') {
      write(1, directories[dir_ind], strlen(directories[dir_ind]));
      write(1, ":\n",2);
      output_entries(directories[dir_ind], aflag, tflag);

      if(dir_ind != dir_size - 1) {
        write(1, "\n", 1);
      }
      else {
        break;
      }
      dir_ind++;
    }
    free(directories);
    return 0;
  }

  // If no non-options arguments were valid directories, open the current directory
  if(directories[0] == NULL && i == optind) {
    directory_name = ".";
    output_entries(directory_name, aflag, tflag);
    free(directories);
    return 0;
  }
  else {
    return 0;
  }
}