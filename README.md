# Bash scripts
A collection of my personal shell scripts. Most of them are centered around terminal-focused workflows, like one would typically have with a window manager (i3/dwm/...)

### Any interesting programs?
- **bri-nozero{,-watcher}**: watches and resists setting display brightness to zero
- **manual-redshift**: allows for finer bluelight-filter control. Just call it with the `up` or `down` argument in your i3/dwm/whatever config.
- **dashboard**: draws a to-do list on your wallpaper from a .md file (CURRENTLY BROKEN)
    - requires `boxes` and compiling sanepr.c (type `make`)
    - pre alpha quality
- **mount-picker-{mount,umount}**: mount/unmount/poweroff disks, without root. Bindable to a key.
- **open-file-somehow**: a substitute for `xdg-open` for opening a file based on extension/mime-type. Much faster and easier to configure.
- **jsondict (endict, jisho)**: look up in two online dicts through API
- **fixxkbmap**: (re)stores my keyboard configuration (layout, repeat rate)
- **poormans, kmsccon-wrapper**: explores a setup without an X server (see comments)
- **ext/pdfunite-with-bookmarks**: merges pdfs and preserves chapters (code from SO, not mine)

## Disclaimer
Although the files work for me, they might do unexpected things on your system. If you're not sure, check the code.
