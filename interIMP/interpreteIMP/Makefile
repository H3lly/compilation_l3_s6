CFLAGS:= -std=gnu99 -Wall
LDFLAGS:= -lfl
CC = gcc
PROGS = interIMP
OBJS = interIMP.yy.o interIMP.tab.o environ.o arbre_syntaxique.o

.PHONY: all clean

all: $(PROGS)

%.o : %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<


interIMP.tab.c interIMP.tab.h: interIMP.y
	bison --file-prefix=interIMP -d interIMP.y

interIMP.yy.c: interIMP.l interIMP.tab.h
	flex -o $@ $<

interIMP: interIMP.tab.o interIMP.yy.o environ.o arbre_syntaxique.o
	$(CC) $(CLIBS) -o $@ $^ $(LDFLAGS)

test: test1 test2 test3 test4 test5 test6 test7 test8 test9

test1:
	./interIMP < ../EXEMPLES/pex1.ip

test2:
	./interIMP < ../EXEMPLES/pex2.ip

test3:
	./interIMP < ../EXEMPLES/pex3.ip

test4:
	./interIMP < ../EXEMPLES/pex4.ip

test5:
	./interIMP < ../EXEMPLES/pex5.ip

test6:
	./interIMP < ../EXEMPLES/pex6.ip

test7:
	./interIMP < ../EXEMPLES/pex7.ip

test8:
	./interIMP < ../EXEMPLES/pex8.ip

test9:
	./interIMP < ../EXEMPLES/pex9.ip

test10:
	./interIMP < ../EXEMPLES/pex10.ip

clean:
	rm *.tab.h *.tab.c *.o interIMP
