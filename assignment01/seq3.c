#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // for getopt

typedef struct {
    double first;
    double incr;
    double last;
    const char *sep;
    const char *term;
} SeqArgs;

int main(int argc, char *argv[]) {
    SeqArgs args = {
        .first = 1.0,
        .incr  = 1.0,
        .last  = 0.0,
        .sep   = "\n",   // default separator
        .term  = "\n"    // default termination
    };

    int opt;

    // --- Parse options ---
    while ((opt = getopt(argc, argv, "s:t:")) != -1) {
        switch (opt) {
            case 's':
                args.sep = optarg;
                break;
            case 't':
                args.term = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s [-s sep] [-t term] [first [incr]] last\n", argv[0]);
                return 1;
        }
    }

    // --- Parse positional arguments ---
    int remaining = argc - optind;
    if (remaining == 1) {
        args.last = atof(argv[optind]);
        args.incr = (args.first > args.last) ? -1 : 1;
    } else if (remaining == 2) {
        args.first = atof(argv[optind]);
        args.last  = atof(argv[optind + 1]);
        args.incr  = (args.first > args.last) ? -1 : 1;
    } else if (remaining == 3) {
        args.first = atof(argv[optind]);
        args.incr  = atof(argv[optind + 1]);
        args.last  = atof(argv[optind + 2]);
    } else {
        fprintf(stderr, "Usage: %s [-s sep] [-t term] [first [incr]] last\n", argv[0]);
        return 1;
    }

    if (args.incr == 0) {
        fprintf(stderr, "Increment cannot be zero\n");
        return 1;
    }

    // --- Print sequence ---
    if (args.incr > 0) {
        for (double i = args.first; i <= args.last; i += args.incr)
            printf("%.0f%s", i, args.sep);
    } else {
        for (double i = args.first; i >= args.last; i += args.incr)
            printf("%.0f%s", i, args.sep);
    }

    printf("%s", args.term);

    return 0;
}
