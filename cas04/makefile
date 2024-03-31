# MAKE - alat koji se koristi za odrzavanje projekata

# pisemo fajl sa nazivom makefile (ili Makefile)

# pozivanje alata: 
#	●  make 
#	●  make clean (za pozivanje cilja clean)

# promenljive za kompajler i opcije
CC = gcc
CFLAGS = -Wall -Wextra

# cilj_pravila: lista_zavisnosti
#	na koji nacin dobijamo cilj_pravila na osnovu liste_zavisnosti

# skracenice:
# 	● $^  -   svi iz liste zavisnosti
# 	● $<  -   prvi u listi zavisnosti
# 	● $@  -   cilj pravila

izvrsni: lex.yy.o parser.o
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
