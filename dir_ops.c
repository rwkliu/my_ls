#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include "dir_ops.h"

int count_entries(char *dir_name) {
  DIR *directory;
  int entries = 0;
  struct dirent *dir_entry;

  directory = opendir(dir_name);

  while(dir_entry = readdir(directory)) {
    entries++;
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