CXX = g++
CXXFLAGS = -Wall -Wextra

izvrsni: lex.yy.o parser.tab.o
	$(CXX) $(CXXFLAGS) $^ -o $@

lex.yy.o: lex.yy.c parser.tab.hpp
	$(CXX) $(CXXFLAGS) -c $<

lex.yy.c: lekser.l parser.tab.hpp
	flex $<

parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CXX) $(CXXFLAGS) -c $<

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $<

.PHONY: clean
clean: 
	rm -f *.o izvrsni lex.yy* parser.tab* parser.output