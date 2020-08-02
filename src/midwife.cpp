#include "config.h"
#include <cstring>
#include <unistd.h>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <cerrno>
#include "src/lexer.hpp"


static void die(const char *arg) {
  fputs(arg, stderr);
  exit(127);
}

static char *program_name;

static void debugPrint(const char ** buffer);

NORETURN void launch (stringVector stringVect);
void launch (stringVector stringVect) {
  size_t end = stringVect.size();
  const char ** newargs = new const char*[end + 1];
  for (size_t i = 0; i < end; ++i) {
    newargs[i] = stringVect[i].c_str();
  }
  newargs[end] = 0;
  //  debugPrint(newargs);
  execvp(newargs[0], const_cast<char *const *>(newargs));
  die("Failed to exec!\n");
}

static void usage(void) {
  fprintf(stderr, "usage: %s (percent-encoded argument) filename ...\n",
          program_name);
}

static void debugPrint(const char ** buffer) {
  const char *string;
  while ((string = *buffer++)) {
    fputs(string, stderr);
    fputc('\n', stderr);
  }
}

enum state { NOTHING, DASH, STAR_DASH };
NORETURN void parseLines (char * numLines, int argc, char **argv);
void parseLines (char * numLines, int argc, char **argv) {
  FILE *fileptr = fopen(argv[0], "r");
  if (NULL == fileptr) {
    die("Cannot open input file\n");
  }
  errno = 0;
  char *ptr = 0;
  unsigned long int numlines;
  {
    char *end;
    numlines = strtoul(numLines, &end, 10);
    if (0 != errno || '\0' != *end) {
      die("bad number of lines\n");
    }
  }

  size_t length;
  for (size_t i = 0; i < numlines; ++i) {
    getline(&ptr, &length, fileptr);
  }
  char *begin = strstr(ptr, "-*-");
  if (NULL == begin) {
    die("missing -*- start token\n");
  }
  else {
    begin += 2;
    *begin = ' ';
    char * end = strlen(begin) + begin - 1;
    enum state status = NOTHING;
    for (char* i = end; i != begin; --i) {
      switch (status) {
        case NOTHING:
          if ('-' == *i) { status = DASH; }
          break;
        case DASH:
          if ('*' == *i) { status = STAR_DASH; }
          else if ('-' == *i) { status = DASH; }
          else { status = NOTHING; }
          break;
        case STAR_DASH:
          if ('-' == *i) {
            *i = '\0';
            launch(lexer(false, begin, static_cast<size_t>(argc), argv));
          }
      }
    }
    die("No -*- end token found\n");
  }
}

int main(int argc, char **argv) {
  program_name = argv[0];
  {
    char * index = program_name + strlen(program_name) - 1;
    if ('2' <= *index && '9' >= *index) {
      if (argc) {
        parseLines(index, argc - 1, argv + 1);
      } else {
        usage();
        return 127;
      }
    } else {
      switch (argc) {
        case 2:
          if (0 == strcmp(argv[1], "--help")) {
            printf("Usage: %s [%%-encoded argument] [script] [script arguments]\n\
       %s -n[0-9] [script] [script argument]\n\
       %s --help\n\
       %s --version\n\
Run 'man midwife' for full documentation\n",
                   argv[0], argv[0], argv[0], argv[0]);
            return 0;
          } else if (0 == strcmp(argv[1], "--version")) {
            puts(PACKAGE_STRING "\nCopyright 2014-2015,2020 Demi Obenour\n\
Report bugs to <" PACKAGE_BUGREPORT ">");
            return 0;
          }
        case 0:
        case 1:
          usage();
          return 127;
        default:
          break;
      }
    }
  }
  if (0 == strncmp(argv[1], "-n", 2)) {
    parseLines(argv[1] + 2, argc - 2, argv + 2);
  }
  /* Parse arguments */
  launch(lexer(true, argv[1], static_cast<size_t>(argc), argv));
}
