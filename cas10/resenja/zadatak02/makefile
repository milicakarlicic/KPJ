CXX = g++
CXXFLAGS = -Wall -Wextra

izvrsni: lex.yy.o parser.tab.o
	$(CXX) $(CXXFLAGS) -o $@ $^
lex.yy.o: lex.yy.c parser.tab.hpp
	$(CXX) $(CXXFLAGS) -c $<
lex.yy.c: lekser.lex
	flex $<
parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CXX) $(CXXFLAGS) -c $<
parser.tab.cpp parser.tab.hpp: parser.ypp
	# -d: parser.tab.hpp
	# -v: parser.output
	bison -d -v $<
	
.PHONY: clean
clean:
	rm -f *.o lex.yy* parser.tab* izvrsni parser.output
