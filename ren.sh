#!/bin/bash
# Removes square brackets and their content from all file names
# "[deleteme] name.md" -> "name.md"

ls | (while read W; do E=`echo "$W" | sed "s/\[.*\] //"`; mv "$W" "$E"; done)
