#!/bin/bash





# Check if redshift is running. If it is not, there is only one
# line with "redshift", the grep process itself.
redshift_is_running=$[$(ps ax | grep redshift | wc -l) - 1]

[ "$redshift_is_running" -gt 0 ] && {
    killall redshift;
    sleep 4;  # wait until it restores previous color to avoid flicker
}

[ -z "$1" ] && {
    redshift -P 2>&1 >/dev/null & 
    disown redshift; 
} || { 
    num=''
    [[ "$1" =~ ^[0-9]+$ ]] || { 
        echo "Argument is not a number" >&2; exit 1; 
    }
    redshift -P -O $1 >/dev/null; 
}

