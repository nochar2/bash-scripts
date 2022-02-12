#include <stdio.h>
#include <string.h>
#define _POSIX_C_SOURCE 200809L

int main(void)
{
    unsigned char *src = getline()
    unsigned int l = strlen(s) + 1
    unsigned char *targ = malloc(l * 3)
    unsigned char *orig_targ = targ;

    while ((*src)++ != '\0') {
        if (*src) <= '\x7f') {
            (*targ)++ = *src;
        } else {
        
        for (int i = 0; i < 2; i++) {
            (*targ)++ = '%';
            char code[2];
            snprintf(code, 2, '%02X', *src);
            for (int j = 0; j < 2; j++) {
                (*targ)++ = *(code + j);
            }
        }
    }

    *targ = '\0';

    puts(orig_targ);
    return 0;
}
