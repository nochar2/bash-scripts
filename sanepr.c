/*
sanepr.c -- place two files in two columns next to each other,
            actually taking wcwidth into account.
*/
#include <stdio.h>
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
        return mk_wcswidth((const wchar_t *)buf, 500);
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
int main(int argc, char **argv)
{
        setlocale(LC_ALL, "en_US.UTF-8");
        (void)argc;
        
        assert(argc == 3 && "expect two files to merge");
        FILE *f = fopen(argv[1], "r");
        FILE *g = fopen(argv[2], "r");

        Readbuf fb = readbuf_wrap(f);
        Readbuf gb = readbuf_wrap(g);
        bool f_has_input, g_has_input;
        f_has_input = g_has_input = true;
        sds fl = sdsempty();
        sds gl = sdsempty();

        int width = 0;

        printf("%d\n", howlongisthis("přeskočil"));
        assert(howlongisthis("přeskočil") == 9);

        int width_of_first = len_of_longest_line_in(argv[1]);

        while (f_has_input || g_has_input) {

                sdsclear(fl);
                sdsclear(gl);

                f_has_input = !sdsreadln(&fb, &fl, '\n');
                g_has_input = !sdsreadln(&gb, &gl, '\n');


                int n_spaces = width_of_first - howlongisthis(fl);
                printf("%s%*s%s\n", fl, n_spaces, "", gl);


                // if (fend) {

                //         printf("%*s", "", 
                // }
        }
        sdsfree(fl);
        sdsfree(gl);
        fclose(f);
        fclose(g);
        
        return 0;
}
