#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    char *sep=",";
    char *term="\n";


int opt;
while ((opt = getopt(argc, argv, "s:t:")) != -1) {
    switch (opt) {
        case 's':
            sep = optarg;
            break;
        case 't':
            term = optarg;
            break;
    }
}

// optind now points to first non-option argument
printf("optind = %d\n", optind);  // prints 5
printf("argv[optind] = %s\n", argv[optind]); // prints "1"
// After getopt() loop
for (int i = optind; i < argc; i++) {
    printf("positional argument: %s\n", argv[i]);
}


}
