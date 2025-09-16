#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int opt;
    int count = 1;           // default repeat count
    int no_newline = 0;      // flag for -n option
    int buf_mode = 2;        // default: fully buffered
    size_t buf_size = 1024;  // default buffer size for line/block buffering

    // Parse options
    while ((opt = getopt(argc, argv, "r:nu:l:b:")) != -1) {
        switch (opt) {
            case 'r':
                count = atoi(optarg);
                if (count < 0) count = 0;
                break;
            case 'n':
                no_newline = 1;
                break;
            case 'u':  // unbuffered
                buf_mode = 0;
                buf_size = 0;
                break;
            case 'l':  // line buffered with specified size
                buf_mode = 1;
                buf_size = (size_t)atoi(optarg);
                if (buf_size <= 0) buf_size = 1024;
                break;
            case 'b':  // block buffered with specified size
                buf_mode = 2;
                buf_size = (size_t)atoi(optarg);
                if (buf_size <= 0) buf_size = 1024;
                break;
            default:
                fprintf(stderr, "Usage: %s [-u] [-l size] [-b size] [-r count] [-n] [msg...]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Build the message from remaining arguments
    if (optind >= argc) {
        fprintf(stderr, "No message provided.\n");
        exit(EXIT_FAILURE);
    }

    char message[1024] = "";
    for (int i = optind; i < argc; i++) {
        strcat(message, argv[i]);
        if (i < argc - 1) strcat(message, " ");
    }

    // Set buffering based on the last buffering option
    switch (buf_mode) {
        case 0:
            setvbuf(stdout, NULL, _IONBF, 0);
            break;
        case 1:
            setvbuf(stdout, NULL, _IOLBF, buf_size);
            break;
        case 2:
            setvbuf(stdout, NULL, _IOFBF, buf_size);
            break;
    }

    // Repeat printing
    for (int i = 0; i < count; i++) {
        for (size_t j = 0; j < strlen(message); j++) {
            putchar(message[j]);
        }
        if (!no_newline) putchar('\n');

        // Flush explicitly if fully buffered
        if (buf_mode == 2) fflush(stdout);
    }

    return 0;
}
