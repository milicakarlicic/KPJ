CXX = g++
CXXFLAGS = -Wall -Wextra

izvrsni: parser.tab.o lex.yy.o polinomi.o
	$(CXX) $(CXXFLAGS) $^ -o $@

polinomi.o: polinomi.cpp polinomi.hpp
	$(CXX) $(CXXFLAGS) -c $<

lex.yy.o: lex.yy.c parser.tab.hpp
	$(CXX) $(CXXFLAGS) -c $<

lex.yy.c: lekser.l parser.tab.hpp polinomi.hpp
	flex $<

parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CXX) $(CXXFLAGS) -c $<

parser.tab.cpp parser.tab.hpp: parser.ypp polinomi.hpp
	bison -d -v $<

.PHONY: clean
clean:
	rm -f *.o parser.tab* lex.yy* izvrsni parser.output