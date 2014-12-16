#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifndef _POSIX_C_SOURCE
# define _POSIX_C_SOURCE 200809L
#endif

#ifndef __cplusplus
# include <stdbool.h>
# include <iso646.h>
#endif

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
# define NORETURN _Noreturn
#elif defined(__cplusplus) && __cplusplus >= 201103L
# define NORETURN [[noreturn]]
#elif defined(__GNUC__) && __GNUC__ > 2 ||      \
  (__GNUC__ == 2 && __GNUC_MINOR__ >= 5)
# define NORETURN __attribute__((noreturn))
#elif !defined(NORETURN)
# define NORETURN
#endif

static NORETURN void die (const char *arg);
static void die(const char *arg) {
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
void usage(void);
void usage(void) {
  fprintf(stderr, "usage: %s (percent-encoded argument) filename ...\n",
          program_name);
}
#if 0
void debugPrint(char ** buffer);
void debugPrint(char ** buffer) {
  char *string;
  while ((string = *buffer++)) {
    fputs(string, stderr);
  }
}
#endif

char * parseLines (char * numLines, char *fileName) {
  char *ptr = 0;
  char *end;
  {
    FILE *fileptr = fopen(fileName, "r");
    if ((FILE*)0 == fileptr) {
      die("Cannot open input file\n");
    }
    errno = 0;
    unsigned long int numlines = strtoul(numLines, &end, 10);
    if (0 != errno || '\0' != *end) {
      die("bad number of lines");
    }

    size_t length;
    off_t linesize;
    for (size_t i = 0; i < numlines; ++i) {
      linesize = getline(&ptr, &length, fileptr);
    }
    fclose(fileptr);
  }
  char *begin = strstr(ptr, "-*-");
  if (NULL == begin) {
    die("missing -*- start token");
  }
  else {
    begin += 3;
    char * end = strlen(begin) + begin - 1;
    for (char* i = end; i != begin; --i) {
      if (0 == strncmp(i, "-*-", 3)) { break; }
    }
    if (end == begin) {
      die("missing -*- end token");
    }
  }
  *end = '\0';
  return begin;
}

/*!re2c */

int main(int argc, char **argv) {
  char * dest[128];
  char **buffer;
  program_name = argv[0];
  size_t bufsize;
  if (argc < 3) {
    usage();
    return 127;
  }
  char *extras = 0;

  size_t numextraargs = 1;
  {
    char *ptr = argv[1];
    char value;
    if (0 == strncmp(ptr, "-n", 2)) {
      extras = parseLines(ptr + 2, argv[2]);
      numextraargs = 3;
    } else {
      while ((value = *ptr++)) {
        if ('&' == value) {
          ++numextraargs;
        }
      }
    }
  }


  /* Subtract one argument for our own name
   * and another for the command string */
  bufsize = (argc + numextraargs - 1);
  buffer = bufsize <= 128 ? dest : (char**)calloc(bufsize, sizeof(char *));
  if (0 == buffer) {
    die("Error allocating memory\n");
  }
  /* Parse arguments */
  if (extras) {
    buffer[0] = "/bin/sh";
    buffer[1] = "-c";
    buffer[2] = extras;
  } else {
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
