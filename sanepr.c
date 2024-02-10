/*
sanepr.c -- place two files in two columns next to each other,
            actually taking wcwidth into account.

            Uses external sds.h and wcwidth.h (stdlib wcwidth is broken)
*/
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include "ext/sds.h"
#include "ext/wcwidth.h"
#include "sdsreadln.c"
#include <wchar.h>
#include <assert.h>

int howlongisthis(const char *s)
{
        wchar_t buf[500] = {0};
        bool got_invalid_char = false;

        int e = mbsrtowcs(buf, &s, 500, NULL);
        assert(e >= 0 && "howlongisthis: non-utf8 garbage in input");

        int len = 0;
        for (wchar_t *pc = (wchar_t *)buf; *pc; pc++) {
                if (*pc == L'\t') { len += 8; continue; }
                int charw = mk_wcwidth(*pc);
                if (charw == -1) { got_invalid_char = true; len += 0; } else { len += charw; }
        }
        if (got_invalid_char) {
                fprintf(stderr, "howlongisthis: garbage characters / control codes in input");
        }
        return len;
}

int len_of_longest_line_in(char *file)
{
        assert(file != NULL);
        int ret;
        static char cmd[BUFSIZ];

        snprintf(cmd, BUFSIZ, "/bin/wc -L %s", file);
        FILE *f = popen(cmd, "r"); assert(f != NULL);
        fscanf(f, "%d", &ret);
        pclose(f);
        return ret;
}


#define MAXFILES 20
#define STR_(x) #x
#define STR(x) STR_(x)

bool any_of(bool *a, int sz) {
        for (int i = 0; i < sz; i++) {
                if (a[i]) return true;
        }
        return false;
}

#define foreach(type, n, col) \
        for (int _i = n, type it=*col; n >= 0; it++, n--)

int main(int argc, char **argv)
{
        // todo: args would be cute also

        const int col_gap = 5;

        int i = 0;
        FILE *ff[MAXFILES];
        int maxwidths[MAXFILES];
        Readbuf rbs[MAXFILES];
        bool has_input[MAXFILES];
        sds lines[MAXFILES];

        int n_files = argc - 1;
        assert(n_files < MAXFILES && "the maximum is " STR(MAXFILES) "files");
                
        setlocale(LC_ALL, "en_US.UTF-8");
        // comparing apples to plums smh
        assert(howlongisthis("křížala") == 7);
        assert(howlongisthis("梅干し") == 6);  

        assert(argc >= 2 && "expected at least one file");

        for (i = 0; i < n_files; i++) {
                ff[i] = fopen(argv[i+1], "r");
                rbs[i] = readbuf_wrap(ff[i]);
                lines[i] = sdsempty();
                maxwidths[i] = len_of_longest_line_in(argv[i+1]);
                has_input[i] = true;
        }


        while(any_of(has_input, n_files)) {
                for (i = 0; i < n_files-1; i++) {
                        sdsclear(lines[i]);
                        has_input[i] = !sdsreadln(&rbs[i], &lines[i], '\n');
                        int pad = maxwidths[i] - howlongisthis(lines[i]);

                        printf("%s%*s%*s", lines[i], pad, "", col_gap, "");
                }
                sdsclear(lines[i]);
                has_input[i] = !sdsreadln(&rbs[i], &lines[i], '\n');
                int pad = maxwidths[i] - howlongisthis(lines[i]);

                printf("%s%*s\n", lines[i], pad, "");
        }

        for (int i = 0; i < n_files; i++) {
                fclose(ff[i]);
                sdsfree(lines[i]);
        }       
        return 0;
}
