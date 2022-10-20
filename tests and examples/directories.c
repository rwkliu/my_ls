#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main() {
  DIR *folder;  //directory handle for the opendir function
  struct dirent *entry; //contains directory entry information
  struct stat filestat; //contains info about a directory entry
  int files = 0;
  long size = 0;

  folder = opendir(".");
  if(folder == NULL) {
    printf("Unable to read directory\n");
    return 1;
  }
  else {
    printf("Directory is opened!\n");
  }

  //Read directory entries
  //S_ISDIR macro is used to test if the st_mode member is a directory
  //or a standard file
  while(entry = readdir(folder)) {
    files++;
    stat(entry->d_name, &filestat);
    if(S_ISDIR(filestat.st_mode)) {
      printf("%d %s: %s    %s\n", files, "Dir", entry->d_name, 
          ctime(&filestat.st_mtim.tv_sec));
    }
    else {
      printf("%d %s: %s %ld %s\n", files, "File", entry->d_name, 
          filestat.st_size, ctime(&filestat.st_mtim.tv_sec));
    }
  }

  closedir(folder);
  return 0;
}