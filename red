#!/bin/sh

# Redshift is a nice red light filter, but nearly impossible to
# configure at runtime, applying the temperature on top of current
# temperature, conflicting with other instances of itself (flickering),
# etc.

# This script allows to set a color (run "red DESIRED_COLOR_TEMP") 
# or run redshift as a daemon (run "red").

isdigit() {
    [ "$1" -eq "$1" ]
}

([ -n "$1" ] && ! isdigit "$1") && { 
    echo "Argument is not a number" >&2; exit 1; 
}

# Check if redshift is running. If not, there is only one line with 
# "redshift", the grep process itself
running_instances=$(ps ax | grep redshift | wc -l)

[ "$running_instances" -gt 1 ] && {
    # SIGKILLing bypasses the long restoring color animation. It will
    # keep the current color, but we'll reset to white before applying
    # an effect with the -P switch.
    killall -KILL redshift;
}

[ -z "$1" ] && {
    redshift -P 2>&1 >/dev/null & 
    disown redshift;
} || { 
    redshift -P -O $1 >/dev/null; 
}

