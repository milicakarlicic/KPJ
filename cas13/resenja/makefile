CXX = g++
CXXFLAGS = -Wall -Wextra

izvrsni: lex.yy.o parser.tab.o naredbe.o izrazi.o
	$(CXX) $(CXXFLAGS) -o $@ $^
lex.yy.o: lex.yy.c parser.tab.hpp naredbe.hpp izrazi.hpp
	$(CXX) $(CXXFLAGS) -c $<
lex.yy.c: lekser.lex
	flex $<
parser.tab.o: parser.tab.cpp parser.tab.hpp naredbe.hpp izrazi.hpp
	$(CXX) $(CXXFLAGS) -c $<
parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $<
naredbe.o: naredbe.cpp naredbe.hpp
	$(CXX) $(CXXFLAGS) -c $<
izrazi.o: izrazi.cpp izrazi.hpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o lex.yy* parser.tab* parser.output izvrsni
