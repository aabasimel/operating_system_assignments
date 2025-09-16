#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // for getopt
#include <string.h>

int main(int argc, char *argv[]){

    int opt;
    int repeat_count = 1;
    int no_newline = 0;

    while((opt = getopt(argc, argv, "r:n"))!=-1){
        switch(opt){
            case 'r':
                repeat_count = atoi(optarg);
                if(repeat_count <0) repeat_count = 0;
                break;
            case 'n':
                no_newline = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-r count] [-n] [msg...]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if(optind >= argc){
        fprintf(stderr, "No message provided. \n");
        exit(EXIT_FAILURE);
    }


    char msg[1024] = "";
    for (int i=optind; i<argc; i++){
        strcat(msg, argv[i]);
        if(i<argc-1) strcat(msg, "");
    }

    setvbuf(stdout, NULL, _IOLBF, 0);
    for (int i=0; i<repeat_count; i++){
        for(size_t j=0; j<strlen(msg);j++){
            putchar(msg[j]);
          
            fflush(stdout);

        }
         putchar('\n');
    }
    return 0;
}