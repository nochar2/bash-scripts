SRC = $(wildcard *.c)
EXE = $(SRC:.c=)

all: $(EXE)
.PHONY: $(EXE) all clean

# took me 20 minutes to find how to do this again ugh
$(EXE): %: %.c
	gcc -g -Wall -Wextra -o $@ $<

clean:
	rm -f $(EXE)


ext/wcwidth/wcwidth.a: ext/wcwidth/wcwidth.c
	gcc -g -o $@ -c $^

