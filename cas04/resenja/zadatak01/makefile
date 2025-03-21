CC = gcc
CFLAGS = -Wall -Wextra

izvrsni: lex.yy.o parser_a.o
	$(CC) $(CFLAGS) -o $@ $^

lex.yy.o: lex.yy.c tokeni.h
	$(CC) $(CFLAGS) -c $<

lex.yy.c: lekser.lex
	flex $<

parser_a.o: parser_a.c tokeni.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o izvrsni lex.yy.c
