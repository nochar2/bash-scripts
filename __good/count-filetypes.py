#!/usr/bin/env python3

import os
import sys

from collections.abc import Iterator
import termplotlib as tpl # type: ignore
#this depends on `python-magic`, not `magic`!
import magic # type: ignore
from collections import Counter

def list_recursively(dir: str) -> Iterator[str]:
    for root, _, files in os.walk(dir):
        for file in files:
            yield os.path.join(root, file)
        
def main() -> None:
    if len(sys.argv) != 2:
        print(f"usage: {sys.argv[0]} DIR/-")
        print(f"counts all files by their MIME type")
        print(f"DIR => list all files in DIR")
        print(f"-   => reads file list from stdin")

        print(f"depends: python-magic, termplotlib")
        print(f"perf: slow, like 300 files a second")
        exit(1)

    mimetypes = {}    
    iterator = None
    if sys.argv[1] == "-":
        iterator = sys.stdin
    else:
        iterator = list_recursively(sys.argv[1])
    
    for line in iterator:
        line = line.rstrip()

        if not os.path.isfile(line):
            continue
            
        mimetype = magic.from_file(line, mime=True)

        if not mimetype in mimetypes:
            mimetypes[mimetype] = 0
        else:
            mimetypes[mimetype] += 1


    fig = tpl.figure()
    types_and_counts = list(mimetypes.items())
    types, counts = zip(*types_and_counts)
    fig.barh(counts, types)
    fig.show()

    # types = list(map(lambda x: x[0], types_and_counts))
    # counts = list(map(lambda x: x[1], types_and_counts))

main()
