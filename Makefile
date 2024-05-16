all: sanepr bri-nozero
bri-nozero: bri-nozero.c
	gcc -g -Wall -Wextra -o $@ $^

sanepr: sanepr.c ext/sds/sds.c
	gcc -g -Wall -Wextra -o $@ $^

ext/wcwidth/wcwidth.a: ext/wcwidth/wcwidth.c
	gcc -g -o $@ -c $^

.PHONY: sanepr
