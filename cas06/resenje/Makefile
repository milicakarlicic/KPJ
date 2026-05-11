# $^ - svi elementi iz liste zavisnosti
# $< - prvi element iz liste zavisnosti
# $@ - cilj pravila

CXX = g++
CXXFLAGS = -Wall -Wextra

izvrsni: parser.o lex.yy.o
	$(CXX) $(CXXFLAGS) $^ -o $@

parser.o: parser.cpp tokeni.hpp
	$(CXX) $(CXXFLAGS) -c $<

lex.yy.o: lex.yy.c tokeni.hpp
	$(CXX) $(CXXFLAGS) -c $<

lex.yy.c: lekser.l
	flex $<

.PHONY: clean
clean: 
	rm -f *.o lex.yy* izvrsni