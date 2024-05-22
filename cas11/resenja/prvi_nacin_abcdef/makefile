CXX = g++
CXXFLAGS = -Wall -Wextra

izvrsni: lex.yy.o parser.tab.o polinomi.o
	$(CXX) $(CXXFLAGS) -o $@ $^
lex.yy.o: lex.yy.c parser.tab.h polinomi.hpp
	$(CXX) $(CXXFLAGS) -c $<
lex.yy.c: lekser.lex
	flex $<
parser.tab.o: parser.tab.cpp polinomi.hpp
	$(CXX) $(CXXFLAGS) -c $<
parser.tab.cpp parser.tab.h: parser.ypp
	bison -d -v $<
poliomi.o: polinomi.cpp polinomi.hpp
	$(CXX) $(CXXFLAGS) -c $<
	
.PHONY: clean
clean:
	rm -f *.o lex.yy* parser.tab* izvrsni parser.output
