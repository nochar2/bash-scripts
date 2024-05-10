all: sanepr bri-nozero
bri-nozero: bri-nozero.c
	gcc -g -Wall -Wextra -o $@ $^

sanepr: sanepr.c ext/sds/sds.c
	gcc -g -Wall -Wextra -o $@ $^

ext/wcwidth.a: ext/wcwidth.c
	gcc -g -o $@ -c $^

.PHONY: sanepr
