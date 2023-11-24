/*
sanepr.c -- place two files in two columns next to each other,
            actually taking wcwidth into account.
*/
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

        int e = mbsrtowcs(buf, &s, 500, NULL);
        assert(e >= 0);
        // this returns -1 for tabs, don't care enough to fix that
        int ret = mk_wcswidth((const wchar_t *)buf, 500);
        return ret;
}

int len_of_longest_line_in(char *file)
{
        assert(file != NULL);
        int ret;
        static char buf[30];
        static char cmd[50];

        snprintf(cmd, 50, "/bin/wc -L %s", file);
        FILE *f = popen(cmd, "r"); assert(f != NULL);
        fgets(buf, sizeof(buf), f);

        sscanf(buf, "%d", &ret);
        return ret;
}

#include <locale.h>

#define MAXFILES 20
#define STR(x) #x

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
        assert(howlongisthis("přeskočil") == 9);

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
