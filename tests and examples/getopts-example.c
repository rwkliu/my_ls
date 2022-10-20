#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Normally, getopt is called in a loop. When getopt returns -1, 
// indicating no more options are present, the loop terminates.
// A switch statement is used to dispatch on the return value from getopt. 
// In typical use, each case just sets a variable that is used later in the program.
// A second loop is used to process the remaining non-option arguments.
int main(int argc, char **argv) {
  int aflag = 0;
  int bflag = 0;
  char *cvalue = NULL;
  int index;
  int c;

  opterr = 0;

  while((c = getopt(argc, argv, "abc:")) != -1) {
    switch(c) {
      case 'a':
        aflag = 1;
        break;
      case 'b':
        bflag = 1;
        break;
      case 'c':
        cvalue = optarg;
        break;
      case '?':
        if (optopt == 'c') {
          fprintf(stderr, "Option -%c requires an argument.\n", optopt);
        }
        else if(isprint(optopt)) {
          fprintf(stderr, "Unknown option '-%c'.\n", optopt);
        }
        else {
          fprintf(stderr, "unknown option character '\\x%x'.\n", optopt);
        }
        return 1;
      default:
        abort();
    }
  }
  printf("aflag = %d, bflag = %d, cvalue = %s\n", aflag, bflag, cvalue);

  for(index = optind; index < argc; index++) {
    printf("Non-option argument %s\n", argv[index]);
  }
  return 0;
}

/*
Example outputs with different combinations of arguments
% testopt
aflag = 0, bflag = 0, cvalue = (null)

% testopt -a -b
aflag = 1, bflag = 1, cvalue = (null)

% testopt -ab
aflag = 1, bflag = 1, cvalue = (null)

% testopt -c foo
aflag = 0, bflag = 0, cvalue = foo

% testopt -cfoo
aflag = 0, bflag = 0, cvalue = foo

% testopt arg1
aflag = 0, bflag = 0, cvalue = (null)
Non-option argument arg1

% testopt -a arg1
aflag = 1, bflag = 0, cvalue = (null)
Non-option argument arg1

% testopt -c foo arg1
aflag = 0, bflag = 0, cvalue = foo
Non-option argument arg1

% testopt -a -- -b
aflag = 1, bflag = 0, cvalue = (null)
Non-option argument -b

% testopt -a -
aflag = 1, bflag = 0, cvalue = (null)
Non-option argument -
*/