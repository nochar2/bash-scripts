#!/usr/bin/env python3

import termplotlib as tpl
import os
import sys
import magic
mime = magic.Magic(mime=True)

def main():
    dirs_dict = {}    

    if len(sys.argv) > 1:
        depth = int(sys.argv[1])
    else:
        depth = 1

    
    for (i, line) in enumerate(sys.stdin):
        # print(f"Line {i}")
        line = line.rstrip()

        if not os.path.isfile(line):
            continue
            
        full_path = line
        toks = full_path.split('/', maxsplit=depth)
        initial = "/".join(toks[:-1])
        if not initial:
            initial = "."

       # mimetype = mime.from_file(line)

        if not initial in dirs_dict:
            dirs_dict[initial] = 0
        else:
            dirs_dict[initial] += 1


    fig = tpl.figure()
    dirs_and_counts = list(dirs_dict.items())
    dirs, counts = zip(*dirs_and_counts)
    fig.barh(counts, dirs)
    fig.show()

    # types = list(map(lambda x: x[0], types_and_counts))
    # counts = list(map(lambda x: x[1], types_and_counts))

main()
