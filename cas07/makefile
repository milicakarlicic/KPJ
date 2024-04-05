CC = gcc
CFLAGS = -Wall -Wextra

izvrsni: parser.o lex.yy.o
	$(CC) $(CFLAGS) -o $@ $^

lex.yy.o: lex.yy.c tokeni.h
	$(CC) $(CFLAGS) -c $<

lex.yy.c: lekser.lex
	flex $<

parser.o: parser.c tokeni.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o izvrsni lex.yy.c
