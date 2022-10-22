//My version of the ls command with -a and -t options
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
// #include "dir_ops.h"
#ifndef STRUCT_DIRENT_ENTRY
#define STRUCT_DIRENT_ENTRY
typedef struct s_dirent_entry {
  char *entry_name;
  time_t t_sec;
  long int t_nsec;
} dirent_entry;
#endif

#ifndef STRUCT_DIRENT_ARRAY
#define STRUCT_DIRENT_ARRAY
typedef struct s_dirent_array {
  int size;
  struct s_dirent_entry **array;
} dirent_array;
#endif

dirent_array *sort_entries(dirent_array *dirents, int tflag) {
  int i = 1;
  int j; 
  dirent_entry *temp_ptr;
  
  //sort entry names alphabetically
  while(i < dirents->size) {
    j = i;
    while(j > 0 && (strcmp(dirents->array[j-1]->entry_name,
           dirents->array[j]->entry_name) > 0)){
      temp_ptr = dirents->array[j];
      dirents->array[j] = dirents->array[j-1];
      dirents->array[j-1] = temp_ptr;
      j--;
      // printf("%d\n", j);
    }
    i++;
    // printf("%d\n", i);
  }

  //Sort by time modified (recent to latest)
  if(tflag == 1) {
    i = 1;
    while(i < dirents->size) {
      j = i;
      while(j > 0 && dirents->array[j-1]->t_sec < dirents->array[j]->t_sec) {
        temp_ptr = dirents->array[j];
        dirents->array[j] = dirents->array[j-1];
        dirents->array[j-1] = temp_ptr;
        j--;
        // printf("%d\n", j);
      }
      i++;
      // printf("%d\n", i);
    }
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
    // printf("%d %s\n", index, dirents->array[index]->entry_name);
    write(1, dirents->array[index]->entry_name, strlen(dirents->array[index]->entry_name));
    write(1, "\n", 1);
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

//Get directory entries (dirents), save them into an array of dirents
//sort the dirents, and print the dirent names 
void output_entries(char *dir_name, int aflag, int tflag) {
  dirent_array entry_array;

  entry_array.size = count_entries(dir_name, aflag);
  // printf("entry_array size: %d\n", entry_array.size);
  get_entries(dir_name, &entry_array, aflag, tflag);
  sort_entries(&entry_array, tflag);
  print_entries(&entry_array);
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
      output_entries(directory_name, aflag, tflag);
    }
  }

  //If no non-options arguments were valid directories, open the current directory
  if(directory_name == NULL && i == optind) {
    directory_name = "/tmp/";
    output_entries(directory_name, aflag, tflag);
    return 0;
  }
  else {
    return 0;
  }
}