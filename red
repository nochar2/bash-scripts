#!/bin/bash

# Redshift is a nice red light filter, but nearly impossible to
# configure at runtime, applying the temperature on top of current
# temperature, conflicting with other instances of itself (flickering),
# etc.

# This script allows to set a color (run "red DESIRED_COLOR_TEMP") 
# or run redshift as a daemon (run "red").

([ -n "$1" ] && ! [[ "$1" =~ ^[0-9]+$ ]]) && { 
    echo "Argument is not a number" >&2; exit 1; 
}

# Check if redshift is running. If not, there is only one line with 
# "redshift", the grep process itself
redshift_is_running=$[$(ps ax | grep redshift | wc -l) - 1]

[ "$redshift_is_running" -gt 0 ] && {
    # SIGKILLing bypasses the long restoring color animation. It will
    # keep the current color, but we'll reset to white before applying
    # an effect with the -P switch. No, I'm not sorry
    killall -KILL redshift;
}

[ -z "$1" ] && {
    redshift -P 2>&1 >/dev/null & 
    disown redshift;
} || { 
    redshift -P -O $1 >/dev/null; 
}

