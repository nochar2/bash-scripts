#include <stdio.h>

int main() {
    const char *HEX = "0123456789ABCDEF";
    char buf[4] = "%  ";
    int c;
    while ((c = getchar()) != -1) {
        if (c & 128) {
            buf[1] = HEX[c / 16];
            buf[2] = HEX[c % 16];
            fputs(buf, stdout);
        } else {
            putchar(c);
        }
    }
}
