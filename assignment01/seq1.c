#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
    double first=1.0, incr=1.0, last;

    if (argc<2){
        fprintf(stderr, "Usage: %s [first[incr]] last\n", argv[0]);
        return 1;

    }
    if(argc==2){
        last=atof(argv[1]);

    }
    else if(argc==3){
        first=atof(argv[1]);
        last=atof(argv[2]);

    }
    else if(argc==4){
        first=atof(argv[1]);
        incr=atof(argv[2]);
        last=atof(argv[3]);
    }
    else{
        fprintf(stderr, "Too many arguments\n");
        return 1;

    }
    for (double i=first; i<=last; i+=incr){
        printf("%.0f\n",i);
    }

    return 0;
}