#define _POSIX_C_SOURCE 200809L
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __GNUC__
# define NORETURN(a) a __attribute__((noreturn))
#else
# if defined __STDC_VERSION__
#  if __STDC_VERSION__ >= 201112L
#   define NORETURN(a) _Noreturn a
#  endif
# endif
#endif
#ifndef NORETURN
# define NORETURN(a) a
#endif
#ifndef __cplusplus
# include <stdbool.h>
# include <iso646.h>
#endif
void NORETURN(die(const char *arg));
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
void usage(void);
void usage(void) {
  fprintf(stderr, "usage: %s (percent-encoded argument) filename ...\n",
          program_name);
}
void debugPrint(char ** buffer);
void debugPrint(char ** buffer) {
  char *string;
  while ((string = *buffer++)) {
    fputs(string, stderr);
  }
}

int main(int argc, char **argv) {
  char ** dest[128];
  char **buffer;
  size_t bufsize;
  if (argc < 3) {
    usage();
    return 127;
  }
  else {
    size_t numextraargs = 1;
    char *result = 0;
    {
      char *ptr, value = '\0';
      for (ptr = argv[1], value = '\0'; (value = *ptr++);) {
        if ('&' == value) {
          ++numextraargs;
        }
      }
      result = argv[1];
    }


    /* Subtract one argument for our one name and another for the command string */
    bufsize = (argc + numextraargs - 1);
    buffer = bufsize <= 128 ? dest : malloc(bufsize * sizeof(char *));
    /* fprintf(stderr, "%zu\n", numextraargs); 
    // Parse arguments */
    { int value = parseArgs(argv[1], buffer, result); if (value) return value; }
    fflush(stderr);
    memcpy(buffer + numextraargs, argv + 2, sizeof(char *) * (argc - 1));
    execv(buffer[0], buffer);
  }
  die("Failed to exec!\n");
}
