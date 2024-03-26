# Bash scripts
A collection of my personal Bash scripts. Most of them are terminal-based and centered around primarily terminal-based workflows, like one would typically have in an i3 environment.

## Why are you publishing this?
If I die tomorrow, how is this going to be useful to the civilization?

### But why should I care?
Have a look around in the code for inspiration and see if there is anything useful.

### Anything specifically useful/interesting?
- **bri-nozero{,-watcher}**: watches and resists setting display brightness to zero
    - 
- **manual-redshift**: allows for finer bluelight-filter control. Just bind the up/down words to your i3/dwm/whatever config.
- **dashboard**: draws a to-do list on your wallpaper from a .md file
    - requires boxes and compiling sanepr.c (type 'make')
    - alpha, has bugs
- **mount-picker-{mount,umount}**: mount/unmount/poweroff disks, without root. Bindable to a key.
- **open-file-somehow**: a substitute (not replacement) for xdg-open for files. A lot faster and easier to configure.
- **weather**: fetches weather info from wttr.in
- **jsondict (endict, jisho)**: look up in two online dicts through API
- **fixxkbmap**: (re)stores my keyboard configuration (layout, repeat rate)
- **poormans, kmsccon-wrapper**: a silly attempt of working without an X server
- **ext/pdfunite-with-bookmarks**: merges pdfs and preserves chapters (code from SO, not mine)

## Things seem broken...
Many of the scripts have a specific configuration or are tied to my configuration / env variables / file structure. Need to keep secrets separate, for example. 

Still, you can create issues, if that would make it better for everyone.
