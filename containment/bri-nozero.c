#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int i = 0;

    char buf[BUFSIZ];
    while (fgets(buf, BUFSIZ, stdin)) {
        // will run twice if line is longer than 256 chars, that
        // won't happen and if it does, it doesn't matter

        char bri_s[7];
        int bri = 0;

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
        //printf("Brightness var is now %d\n", brightness);
        if (bri == 0) {
            system("brightnessctl set 1");
        }

        printf("%d\n", bri);

        i++;
    }
    
}
