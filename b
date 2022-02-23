#!/bin/bash
[ -z "$1" ] && { exit 1; }
[ "$1" -eq "$1" ] || { echo "Not a number"; exit 2; }
[ "$1" -eq 0 ] && { echo "0 % brightness is not allowed"; exit 3; }
brightnessctl set $1%

