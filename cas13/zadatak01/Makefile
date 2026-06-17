CXX = g++
CXXFLAGS = -Wall

izvrsni: parser.tab.o lex.yy.o funkcije.o
	$(CXX) $(CXXFLAGS) $^ -o $@

funkcije.o: funkcije.cpp funkcije.hpp
	$(CXX) $(CXXFLAGS) -c $<

lex.yy.o: lex.yy.c parser.tab.hpp 
	$(CXX) $(CXXFLAGS) -c $<

lex.yy.c: lekser.l parser.tab.hpp funkcije.hpp
	flex $<

parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CXX) $(CXXFLAGS) -c $<

parser.tab.cpp parser.tab.hpp: parser.ypp funkcije.hpp
	bison -d -v $<

.PHONY: clean
clean:
	rm -f *.o parser.tab* lex.yy* izvrsni parser.output