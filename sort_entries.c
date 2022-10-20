#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>

#ifndef STRUCT_DIRENT_ARRAY
#define STRUCT_DIRENT_ARRAY
typedef struct s_dirent_array {
  int size;
  struct dirent **array;
} dirent_array;
#endif

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

int main() {
  DIR *folder;
  struct dirent *entry;
  struct stat filestat;
  dirent_array entry_array;
  int index = 0;
  char *directory_name = ".";

  entry_array.size = count_entries(directory_name);
  folder = opendir(directory_name);

  entry_array.array = malloc(entry_array.size * sizeof(struct dirent *));

  //Read directory entries and assign dirent_array->array point to the entries
  while(entry = readdir(folder)) {
    entry_array.array[index] = entry;
    printf("Entry %d: %s\n", index, entry_array.array[index]->d_name);
    index++;
  }

  struct dirent *dirent_temp = entry_array.array[0];
  entry_array.array[0] = entry_array.array[1];
  entry_array.array[1] = dirent_temp;

  printf("Switched entries\n");
  index = 0;
  while(entry_array.array[index] != NULL) {
    printf("Entry %d: %s\n", index, entry_array.array[index]->d_name);
    index++;
  }
  
  free(entry_array.array);
  closedir(folder);
  return 0;
}