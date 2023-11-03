#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char buf[BUFSIZ];

    // each time I get something on stdin
    while (fgets(buf, BUFSIZ, stdin)) {
        char bri_s[8] = {0};
        int bri = 0;

        // read brightness
        FILE *bri_file = fopen("/sys/class/backlight/intel_backlight/brightness", "r");
        if (!bri_file) {
            perror("cannot open file");
            return 1;
        }
        fread(bri_s, 7, 1, bri_file);
        sscanf(bri_s, "%d", &bri);
        // printf("str: -%s-, int: -%d-\n", bri_s, bri);
        fclose(bri_file);

        //fscanf(bri_file, "%6d", &brightness);
        if (bri == 0) {
            system("brightnessctl set 1");
        }
    }
}
