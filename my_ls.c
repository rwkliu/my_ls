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
  for(i = optind; i < argc; i++) {
    if(check_dir(argv[i]) == 1) {
      printf("Unable to open directory\n");
    }
    else {
      directory_name = argv[i];
      entry_array.size = count_entries(directory_name, aflag);
      get_entries(directory_name, &entry_array, aflag, tflag);
      sort_entries(&entry_array, tflag);
      if(argc - optind >= 2) {
        printf("%s:\n", directory_name);
        print_entries(&entry_array);
        printf("\n");
      }
      else {
        print_entries(&entry_array);
      }
    }
  }

  //If no non-options arguments were valid directories, open the current directory
  if(directory_name == NULL && i == optind) {
    directory_name = ".";
    entry_array.size = count_entries(directory_name, aflag);
    get_entries(directory_name, &entry_array, aflag, tflag);
    sort_entries(&entry_array, tflag);
    print_entries(&entry_array);
    return 0;
  }
  else {
    return 0;
  }
}