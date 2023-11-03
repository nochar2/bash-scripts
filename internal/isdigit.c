#include <stdio.h>
#include <ctype.h>

void usage() {
    puts("Usage: isnum STRING, checks if STRING is only of digits 0-9.\n"
         "Doesn't check for minus signs or E notation or decimals or whatever else");
}

int main(int argc, char **argv) {
    if (argc != 2) {
        usage();
        return 2;
    }
    char *s = argv[1];
    if (!(*s)) {  // zero length
        return 1;
    }
    for (; *s; s++) {
        if (!(isdigit(*s))) {
            return 1;
        }
    }
    return 0;
}
