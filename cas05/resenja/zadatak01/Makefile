a.out: parser_b.o lex.yy.o
	g++ parser_b.o lex.yy.o 

parser_a.o: parser_a.cpp tokeni.hpp
	g++ -c parser_a.cpp	

parser_b.o: parser_b.cpp tokeni.hpp
	g++ -c parser_b.cpp	

lex.yy.o: lex.yy.c tokeni.hpp
	g++ -c lex.yy.c	

lex.yy.c: lekser.l tokeni.hpp
	flex lekser.l

.PHONY: clean
clean:
	rm -f a.out *.o lex.yy*