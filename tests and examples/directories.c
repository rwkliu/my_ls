#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

int main() {
  DIR *folder = opendir(".");  //directory handle for the opendir function
  struct dirent *entry; //contains directory entry information
  struct stat filestat; //contains info about a directory entry
  int files = 0;

  while((entry = readdir(folder)) != NULL) {
    files++;
    stat(entry->d_name, &filestat);
    printf("%d: %s %s", files, entry->d_name, ctime(&filestat.st_mtim.tv_sec));
  }

  closedir(folder);
  return 0;
}