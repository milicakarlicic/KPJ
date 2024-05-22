CXX = g++
# opcija -g ukoliko zelimo da odredimo u kojim linijama imamo curenje memorije koriscenjem valgrind-a
CXXFLAGS = -Wall -Wextra -g

izvrsni: lex.yy.o parser.tab.o polinomi.o
	$(CXX) $(CXXFLAGS) -o $@ $^
lex.yy.o: lex.yy.c parser.tab.hpp polinomi.hpp
	$(CXX) $(CXXFLAGS) -c $<
lex.yy.c: lekser.lex
	flex $<
parser.tab.o: parser.tab.cpp parser.tab.hpp polinomi.hpp
	$(CXX) $(CXXFLAGS) -c $<
parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $<
polinomi.o: polinomi.cpp polinomi.hpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o parser.tab* lex.yy* izvrsni parser.output
