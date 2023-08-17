#include <stdio.h>

int main() {
    const char *HEX = "0123456789ABCDEF";
    const size_t in_size = 1<<12;
    char in[in_size];
    char out[in_size * 3];

    // reading strings is faster than calling getchar many times
    // about twice as fast on /dev/urandom
    while ((fgets(in, in_size, stdin)) != NULL) {
        size_t out_i = 0;

        for (char *s = in; *s; s++) {
            unsigned char c = *s;

            if (c & 128 || c == ' ') {
                out[out_i++] = '%';
                out[out_i++] = HEX[c / 16];
                out[out_i++] = HEX[c % 16];
            } else {
                out[out_i++] = c;
            }
        }
        out[out_i] = '\0';
        fputs(out, stdout);
    }
}

