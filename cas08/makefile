CC = gcc
CFLAGS = -Wall -Wextra

izvrsni: lex.yy.o y.tab.o
	$(CC) $(CFLAGS) -o $@ $^
lex.yy.o: lex.yy.c y.tab.h
	$(CC) $(CFLAGS) -c $<
lex.yy.c: lekser.lex
	flex $<
y.tab.o: y.tab.c y.tab.h
	$(CC) $(CFLAGS) -c $<
y.tab.c y.tab.h: parser.y
	# -d: y.tab.h
	# -v: y.output
	yacc -d -v $<

.PHONY: clean
clean:
	rm -f *.o lex.yy* y.tab* izvrsni y.output
