#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "dir_ops.h"

//Count the number of entries in the directory
//If aflag = 1, the hidden files are counted
int count_entries(char *dir_name, int aflag) {
  DIR *directory;
  int entries = 0;
  struct dirent *dir_entry;

  directory = opendir(dir_name);

  while(dir_entry = readdir(directory)) {
    if(aflag == 0) {
      if(strncmp(dir_entry->d_name,".", 1) != 0){
        entries++;
      }
    }
    else {
      entries++;
    }
  }
  closedir(directory);
  return entries;
}

//Check if directory is found
int check_dir(char *directory) {
  DIR *dir = opendir(directory);
  if(dir == NULL) {
      return 1;
    }
  else {
    return 0;
  }
}