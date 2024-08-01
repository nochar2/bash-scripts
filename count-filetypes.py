#!/usr/bin/env python3

import termplotlib as tpl

import os
import sys
import magic
from collections import Counter
mime = magic.Magic(mime=True)

def main():
    mimetypes = {}    
    
    for (i, line) in enumerate(sys.stdin):
        # print(f"Line {i}")
        line = line.rstrip()


        if not os.path.isfile(line):
            continue
            
        mimetype = mime.from_file(line)

        if not mimetype in mimetypes:
            mimetypes[mimetype] = 0
        else:
            mimetypes[mimetype] += 1

    print(mimetypes)

    fig = tpl.figure()
    types_and_counts = list(mimetypes.items())
    types, counts = zip(*types_and_counts)
    fig.barh(counts, types)
    fig.show()

    # types = list(map(lambda x: x[0], types_and_counts))
    # counts = list(map(lambda x: x[1], types_and_counts))




	

main()
