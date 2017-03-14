.PHONY: clean all

all:
	flex test2.l
	cc lex.yy.c -o test2


clean:
	@rm -rf *.~ lex.yy.c test2