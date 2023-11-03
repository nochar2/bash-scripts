#!/bin/sh
usage()
{
  echo "Sets brightness using   brightnessctl set xx%.   Refuses to set zero brightness."
}


[ -z "$1" ] && { usage; exit 0; }
[ "$1" -eq "$1" ] || { echo "Not a number"; exit 2; }
[ "$1" -eq 0 ] && { brightnessctl set 1; exit 0; }
brightnessctl set "$1"%

