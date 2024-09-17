#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "sds/sds.c"

typedef int64_t s64;
typedef uint64_t u64;
typedef bool is_eof;
#define SDBUFSIZ 8192

typedef char *sds;
typedef struct {
    FILE *file;
    char buf[SDBUFSIZ + 1];  // extra sentinel space
    s64 start;
    s64 end;
} Readbuf;

Readbuf readbuf_wrap(FILE *file) {
    return (Readbuf) {file, {0}, 0, 0};
}

is_eof sdsreadln(Readbuf *s, sds *out, char eol) {
    /* buffer has at most n-1 characters left from last time
     * start == end means no characters are left */

    assert(s->start >= 0);
    assert(s->start <= SDBUFSIZ);
    assert(s->end >= 0);
    assert(s->end <= SDBUFSIZ);
    assert(s != NULL);
    assert(out != NULL && "discarding input might be done later\n"
           "rn I don't know how to do it without having really disgusting code");


    static s64 read_so_far = 0;
    if (read_so_far % 10000 == 0) {
         //DEBUG("read %9.1d bytes so far\n", read_so_far);
    }
    // if it is, allocate sdsempty there once we need to write some data

    const bool read_nothing_eof = true;

    /* no leftovers? */
    if (s->start == s->end) {
        // DEBUG("s->start %u, s->end %u\n", s->start, s->end);
        s->start = 0;
        s->end = (s64)fread(s->buf, 1, SDBUFSIZ, s->file);  // make an issue if you need 8+ EB reads
        if (s->end == 0) {  // read nothing
            return read_nothing_eof;
        }
    }

    /* maybe EOL is in the buffer from last time? */
    char sentinel = eol;
    s->buf[s->end] = sentinel;

    // much faster than manually looping byte by byte
    char *eoladdr = memchr(s->buf + s->start, eol, (u64)(s->end - s->start + 1));
    assert(eoladdr != NULL && "it's either in the data or a sentinel, has to be nonnull");
    ptrdiff_t eolpos = eoladdr - s->buf;

    if (*out == NULL) {
        *out = sdsempty();
    }
    assert(eolpos - (s64)s->start >= 0);
    *out = sdscatlen(*out, s->buf + s->start, (u64)(eolpos - s->start));

    // found it
    if (eolpos < s->end) {
        read_so_far += (eolpos - s->start);
        s->start = eolpos+1;
        return !read_nothing_eof;
    }

    /* if not, read the whole buffer again until you find the EOL or you reach EOF */
    s->start = 0;
    s->end = SDBUFSIZ;

    while (0 != s->end) {  // no EOF yet
        s->end = (s64)fread(s->buf, 1, SDBUFSIZ, s->file);

        s->buf[s->end] = sentinel;
        char *eoladdr = memchr(s->buf + s->start, eol, (u64)(s->end - s->start + 1));
        assert(eoladdr != NULL && "it's either in the data or a sentinel, has to be nonnull");
        eolpos = eoladdr - s->buf;

        /* flush what you have read so far */
        *out = sdscatlen(*out, s->buf, (u64)eolpos);
        read_so_far += eolpos;

        if (eolpos < s->end) {
            s->start = eolpos;
            return !read_nothing_eof;
        }

        /* jump over the EOL separator for later reads */
    }

    s->start = 0;
    s->end = 0;
    // DEBUG("exiting sdsreadln, eof\n");
    return read_nothing_eof;
}
