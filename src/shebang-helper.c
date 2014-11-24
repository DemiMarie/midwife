#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
char *program_name;
void parseArgs(char *string, char ** buffer);
void die(char *string) {
    fputs(string, stderr);
    exit(127);
}

void usage(void) {
    fprintf(stderr, "usage: %s (percent-encoded argument) filename ...\n",
            program_name);
}
int main(int argc, char **argv) {
    char ** buffer;
    if (argc < 3) {
        usage();
    }
    else {
        size_t numextraargs = 1;
        {
            char *ptr, value = '\0';
            for (ptr = argv[1], value = '\0'; (value = *ptr++);) {
                if ('&' == value) {
                    ++numextraargs;
                }
            }
        }

        // Subtract one argument for our one name and another for the command string
        buffer = malloc(sizeof(char *) * (argc + numextraargs - 2));

        // Parse arguments
        parseArgs(argv[1], buffer);
        memcpy(buffer + numextraargs, argv + 2, sizeof(char *) * (argc - 1));
        execv(buffer[0], buffer);
    }
}

