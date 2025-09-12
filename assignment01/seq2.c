#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    double first, incr, last;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [first [incr]] last\n", argv[0]);
        return 1;
    }

    if (argc == 2) {
        // Only last provided
        last = atof(argv[1]);
        if (last >= 1) {
            first = 1;
            incr  = 1;
        } else {
            first = -1;
            incr  = -1;
        }
    } 
    else if (argc == 3) {
        // first and last provided
        first = atof(argv[1]);
        last  = atof(argv[2]);
        incr  = (first <= last) ? 1 : -1;
    } 
    else if (argc == 4) {
        // first, incr, last provided
        first = atof(argv[1]);
        incr  = atof(argv[2]);
        last  = atof(argv[3]);

        // Check if increment points in the wrong direction
        if ((first < last && incr <= 0) || (first > last && incr >= 0)) {
            fprintf(stderr, "Error: since %.0f is larger than %.0f, incr must be negative\n", first, last);
            return 1;
        }
    } 
    else {
        fprintf(stderr, "Too many arguments\n");
        return 1;
    }

    // Generate the sequence
    if (incr > 0) {
        for (double i = first; i <= last; i += incr)
            printf("%.0f\n", i);
    } else {
        for (double i = first; i >= last; i += incr)
            printf("%.0f\n", i);
    }

    return 0;
}
