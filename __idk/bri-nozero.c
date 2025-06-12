#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// written in C because the shell version was too slow
int main() {
    char buf[BUFSIZ];

    // each time I get something on stdin
    while (fgets(buf, BUFSIZ, stdin)) {
        char bri_s[8] = {0};
        int bri = 0;

        // read brightness
        {
            FILE *fh = fopen("/sys/class/backlight/intel_backlight/brightness", "r");
            if (!fh) {
                perror("cannot open file");
                return 1;
            }
            fread(bri_s, 7, 1, fh);
            sscanf(bri_s, "%d", &bri);
            fclose(fh);
        }

        if (bri == 0) {
            system("brightnessctl set 1");
        }
    }
}
