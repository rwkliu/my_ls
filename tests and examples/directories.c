#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>

int main() {
  DIR *folder = opendir("/home");  //directory handle for the opendir function
  struct dirent *entry; //contains directory entry information
  struct stat filestat; //contains info about a directory entry
  int files = 0;
  char *path = strdup("/home/");
  int input_path_len = strlen(path);

  while((entry = readdir(folder)) != NULL) {
    files++;
    path = realloc(path, strlen(path) + strlen(entry->d_name)* sizeof(char));
    strcat(path, entry->d_name);
    int stat_result = stat(path, &filestat);
    if(stat_result == -1) {
      printf("Errno: %d\n", errno);
      printf("Unable to get file properties\n");
    }
    else {
      printf("%d: %s %s", files, entry->d_name, ctime(&filestat.st_mtim.tv_sec));
    }
    path[input_path_len] = '\0';
  }

  closedir(folder);
  return 0;
}