#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#ifndef _POSIX_C_SOURCE
# define _POSIX_C_SOURCE 200809L
#endif
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <vector>
#include <string>

#include "lexer.hpp"


void die(const char *arg) {
  fputs(arg, stderr);
  exit(127);
}

static char *program_name;
int parseHex(char a);
int parseHex(char a) {
  if ('0' <= a && a <= '9') {
    return a - '0';
  } else if ('a' <= a && a <= 'f') {
    int value = a - 'a';
    return value + 10;
  } else if ('A' <= a && a <= 'F') {
    int value = a - 'A';
    return value + 10;
  } else {
    die("Bad %- escape\n");
  }
}


int parseArgs(char *string, char ** buffer, char *dest);
int parseArgs(char *string, char ** buffer, char *dest) {
  char *cursor = dest;
  size_t numArg = 0;
  const char *ptr = string;
  buffer[numArg++] = dest;
  while(true) {
    char value = *ptr++;
    int result;
    switch (value) {
      case '&': *cursor++ = '\0';
        buffer[numArg++] = cursor;
        break;
      case '+': *cursor++ = ' ';
        break;
      case '%':
        result = 16 * parseHex(*ptr++);
        result += parseHex(*ptr++);
        *cursor++ = (result > 127) ? result - 256 : result;
        break;
      case '\0':
        *cursor = '\0';
        buffer[numArg] = (char *)0;
        return 0;
      default: *cursor++ = value;
        break;
    }
  }
}
void debugPrint(const char ** buffer);

NORETURN void launch (stringVector stringVect);
void launch (stringVector stringVect) {
  size_t end = stringVect.size();
  const char ** newargs = new const char*[end + 1];
  for (size_t i = 0; i < end; ++i) {
    newargs[i] = stringVect[i].c_str();
  }
  newargs[end] = (char *)0;
  //  debugPrint(newargs);
  execv((const char *)newargs[0], (char * const *)newargs);
  die("Failed to exec!\n");
}
void usage(void);
void usage(void) {
  fprintf(stderr, "usage: %s (percent-encoded argument) filename ...\n",
          program_name);
}
void debugPrint(const char ** buffer) {
  const char *string;
  while ((string = *buffer++)) {
    fputs(string, stderr);
    fputc('\n', stderr);
  }
}

enum state { NOTHING, DASH, STAR_DASH };
NORETURN void parseLines (char * numLines, int argc, char **argv);
void parseLines (char * numLines, int argc, char **argv) {
  FILE *fileptr = fopen((char*)(argv[0]), "r");
  if ((FILE*)0 == fileptr) {
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
  off_t linesize;
  for (size_t i = 0; i < numlines; ++i) {
    linesize = getline(&ptr, &length, fileptr);
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
            launch(lexer(begin, i - begin, argc, argv));
          }
      }
    }
    die("No -*- end token found\n");
  }
}

int main(int argc, char **argv) {
  char * dest[128];
  char **buffer;
  program_name = argv[0];
  {
    char * index = program_name + strlen(program_name) - 1;
    if ('2' <= *index && '9' >= *index) {
      if (argc < 2) { 
        usage(); 
        return 127;
      }
      parseLines(index, argc - 1, argv + 1);
    }
  }
  size_t bufsize;
  if (argc < 3) {
    usage();
    return 127;
  }
  size_t numextraargs = 1;
  {
    char *ptr = argv[1];
    char value;
    if (0 == strncmp(ptr, "-n", 2)) {
      parseLines(ptr + 2, argc - 2, argv + 2);
    } else {
      while ((value = *ptr++)) {
        if ('&' == value) {
          ++numextraargs;
        }
      }
    }
  }


  /* Subtract one argument for our one name
   * and another for the command string */
  bufsize = (argc + numextraargs - 1);
  buffer = bufsize <= 128 ? dest : (char**)calloc(bufsize, sizeof(char *));
  if (0 == buffer) {
    die("Error allocating memory\n");
  }
  /* Parse arguments */
  {
    char *result = argv[1];
    int value = parseArgs(argv[1], buffer, result);
    if (value) {
      return value;
    }
  }
  fflush(stderr);
  memcpy(buffer + numextraargs, argv + 2, sizeof(char *) * (argc - 1));
  execv(buffer[0], buffer);
  die("Failed to exec!\n");
}
