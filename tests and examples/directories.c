#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

int main() {
  DIR *folder = opendir("/home");  //directory handle for the opendir function
  struct dirent *entry; //contains directory entry information
  struct stat filestat; //contains info about a directory entry
  int files = 0;

  while((entry = readdir(folder)) != NULL) {
    files++;
    if(stat(entry->d_name, &filestat) == -1) {
      printf("Unable to get file properties\n");
    }
    else {
      printf("%d: %s %s", files, entry->d_name, ctime(&filestat.st_mtim.tv_sec));
    }
  }

  closedir(folder);
  return 0;
}