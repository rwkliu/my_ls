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
  int index = 0;
  int curr_opt;
  char *directory_name = NULL;
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
    // printf("Non-option argument %d %s\n", i, argv[i]);
    if(check_dir(argv[i]) == 1) {
      printf("Unable to open directory\n");
      return 1;
    }
    else {
      directory_name = argv[i];
      // printf("directory_name %s\n", directory_name);
    }
  }

  //If no non-options arguments were valid directories, open the current directory
  if(directory_name == NULL) {
    directory_name = ".";
  }
  
  //Get directory entries and save in entry_array
  entry_array.size = count_entries(directory_name, aflag);
  get_entries(directory_name, &entry_array, aflag, tflag);
  sort_entries(&entry_array, aflag, tflag);
  
  //Print entry_name, t_sec, and t_nsec of each directory entry
  while(index < entry_array.size) {
    printf("%s\n", entry_array.array[index]->entry_name);
    // printf("Entry %d: %s\n", index, entry_array.array[index]->entry_name);
    // printf("time in HH:MM:SS: %s", ctime(&entry_array.array[index]->t_sec));
    // printf("time in nanoseconds: %ld\n\n", entry_array.array[index]->t_nsec);
    index++;
  }
  return 0;
}