#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include "dir_ops.h"

//Implement: Sort entries by tv_sec and tv_nsec
//Sort dirent_array entries
dirent_array *sort_entries(dirent_array *dirents, int aflag, int tflag) {
  int i = 1;
  int j; 
  dirent_entry *temp_ptr;

  while(i < dirents->size) {
    j = i;
    while(j > 0 && (strcmp(dirents->array[j-1]->entry_name,
           dirents->array[j]->entry_name) > 0)){
      temp_ptr = dirents->array[j];
      dirents->array[j] = dirents->array[j-1];
      dirents->array[j-1] = temp_ptr;
      j--;
    }
    i++;
  }
  
  return dirents;
}

//Get each entry d_name, tv_sec, and tv_nsec values
//If aflag = 1, the hidden file entries are added to the dirent_array
dirent_array *get_entries(char *dir_name, dirent_array *dirents, int aflag, int tflag) {
  int index = 0;
  struct stat filestat;
  struct dirent *entry;
  DIR *folder = opendir(dir_name);
  dirents->array = malloc(dirents->size * sizeof(dirent_entry *));

  while((entry = readdir(folder)) && index < dirents->size) {
    if(aflag == 0) {
      if(strncmp(entry->d_name, ".", 1) == 0) {
        continue;
      }
    }
    
    dirents->array[index] = malloc(sizeof(dirent_entry));
    dirents->array[index]->entry_name = entry->d_name;
    stat(entry->d_name, &filestat);
    dirents->array[index]->t_sec = filestat.st_mtim.tv_sec;
    dirents->array[index]->t_nsec = filestat.st_mtim.tv_nsec;
    index++;
  }
  closedir(folder);
  return dirents;
}

//Print entry names
void print_entries(dirent_array *dirents) {
  int index = 0;

  while(index < dirents->size) {
    printf("%s\n", dirents->array[index]->entry_name);
    index++;
  }
}

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
  closedir(dir);
}