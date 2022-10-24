#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>

int main() {
  char *file_path = "/home/";
  DIR *folder = opendir(file_path);  //directory handle for the opendir function
  struct dirent *entry; //contains directory entry information
  struct stat filestat; //contains info about a directory entry
  int files = 0;
  int stat_result;
  char *path = strdup(file_path);
  int file_path_len = strlen(path);

  if(strcmp(file_path, ".") != 0) {
    if(file_path[strlen(file_path)] != '/') {
      path = realloc(path, strlen(path) + 1 * sizeof(char));
      strcat(path, "/");
      file_path_len = strlen(path);
    }
  }

  while((entry = readdir(folder)) != NULL) {
    files++;
    if(strcmp(file_path, ".") != 0) {
      path = realloc(path, strlen(path) + strlen(entry->d_name) * sizeof(char));
      strcat(path, entry->d_name);
      stat_result = stat(path, &filestat);
    }
    else {
      stat_result = stat(path, &filestat);
    }
    
    if(stat_result == -1) {
      printf("Errno: %d\n", errno);
      printf("Unable to get file properties\n");
    }
    else {
      printf("%d: %s %s", files, entry->d_name, ctime(&filestat.st_mtim.tv_sec));
    }
    path[file_path_len] = '\0';
  }

  closedir(folder);
  return 0;
}