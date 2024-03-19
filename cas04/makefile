# promenljive za kompajler i opcije
CC = gcc
CFLAGS = -Wall -Wextra

# cilj_pravila: lista_zavisnosti
#	na koji nacin dobijamo cilj_pravila na osnovu liste_zavisnosti

# skracenice:
# $^     svi iz liste zavisnosti
# $<     prvi u listi zavisnosti
# $@     cilj pravila

izvrsni: lex.yy.o parser.o
	$(CC) $(CFLAGS) -o $@ $^

lex.yy.o: lex.yy.c tokeni.h
	$(CC) $(CFLAGS) -c $<

lex.yy.c: lexer.lex
	flex $<
	
parser.o: parser.c tokeni.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o izvrsni lex.yy.c
