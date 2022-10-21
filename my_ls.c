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
  DIR *folder = NULL;
  int aflag = 0;
  int tflag = 0;
  int index = 0;
  int curr_opt;
  char *directory_name;
  struct dirent *entry;
  struct stat filestat;
  dirent_array entry_array;
  
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
  for(int i = optind; i < argc; i++) {
    printf("Non-option argument %d %s\n", i, argv[i]);
    if(check_dir(argv[i]) == 1) {
      printf("Unable to open directory\n");
      return 1;
    }
    else {
      directory_name = argv[i];
    }
  }

  //If no non-options arguments were valid directories, open the current directory
  if(folder == NULL) {
    directory_name = ".";
  }

  //Read directory entries and assign dirent_array->array point to the entries
  entry_array.size = count_entries(directory_name, aflag);
  folder = opendir(directory_name);
  entry_array.array = malloc(entry_array.size * sizeof(struct dirent *));
  while((entry = readdir(folder)) && index < entry_array.size) {
    entry_array.array[index] = entry;
    printf("Entry %d: %s\n", index, entry_array.array[index]->d_name);
    index++;
  }

  closedir(folder);
  return 0;
}