# MAKE - alat koji se koristi za odrzavanje projekata

# pisemo fajl sa nazivom Makefile (ili makefile) u kojem se nalaze pravila za izgradnju projekta

# pozivanje alata: 
#  	 make 
#	 make clean (za pozivanje cilja clean)

izvrsni: parser.o lex.yy.o
	g++ parser.o lex.yy.o -o izvrsni

parser.o: parser.cpp tokeni.hpp
	g++ -c parser.cpp

lex.yy.o: lex.yy.c
	g++ -c lex.yy.c

lex.yy.c: lekser.l tokeni.hpp
	flex lekser.l

.PHONY: clean
clean:
	rm -f a.out lex.yy.c *.o izvrsni 