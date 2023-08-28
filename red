#!/bin/sh

# date +"%s.%N"  -- for benchmarking, takes about 50 ms rn which is very slow but whatever

usage() {
     echo "usage: $0 TEMP|up|down"
     echo "TEMP    color temperature from 1000 to 25000 K"
     echo "down    multiplies current temp by 1.1, capping at 6500 K (white)"
     echo "up      divides current temp by 1.1, capping at 1000 K (red)"
}

isdigit() {
    [ "$1" -eq "$1" ]
}

min() {
    echo $(( $1 < $2 ? $1 : $2 ))
}

max() {
    echo $(( $1 > $2 ? $1 : $2 ))
}

[ -z "$1" ] && { usage; exit 0; }

max_temp=6500
min_temp=1000

current_temp=$(cat /tmp/red-colortemp)

# failsafes: when running this script 20+ times a second (holding a key),
# sometimes the file would be cleared without any value being set.
# This fixes it hopefully
[ -z "$current_temp" ] && current_temp=6500
echo "$current_temp" > "/tmp/red-colortemp"

# fixme: this shouldn't ever happen

if [ "$1" = "up" ]; then
    desired_temp=$(min "$max_temp" "$(echo "($current_temp * 1.1) / 1" | bc)")
elif [ "$1" = "down" ]; then
    desired_temp=$(max "$min_temp" "$(echo "$current_temp / 1.1" | bc)")
elif isdigit "$1"; then
    desired_temp=$1
else
    echo "Argument is not a number" >&2; exit 1; 
fi

# output asap, not after waiting ~30 ms for redshift to do its job
echo "$desired_temp" > "/tmp/red-colortemp"

# bypass the long restore animation. 
# Unconditional, it's much faster than pgrep
killall -KILL redshift 2>/dev/null


lastid=$(cat /tmp/last-notification)
[ -n "$lastid" ] && lastid_switch="-r $lastid" || lastid_switch=""
# shellcheck disable=SC2086
newid=$(notify-send $lastid_switch -p -t 700 "red" "Setting scrren color temp to ${desired_temp}K")
redshift -P -O "$desired_temp" >/dev/null
echo "$newid" > /tmp/last-notification
