CC = gcc
CFLAGS = -Wall -Wextra

OUT = ecode

all: $(OUT)

$(OUT): helptext.h main.c
	$(CC) $(CFLAGS) main.c -o $(OUT)

helptext.h: helptext.txt
	help-text -i helptext.txt -o helptext.h

clean:
	@(RM) $(OUT)
