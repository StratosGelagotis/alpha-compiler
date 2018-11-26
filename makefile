CC=g++ -std=c++11

all:make make5

make:lex.yy.c delete2.tab.c sym.cpp phase3.cpp phase4.cpp phase5.cpp
	$(CC)  lex.yy.c delete2.tab.c sym.cpp phase3.cpp phase4.cpp -o compile.out
	
make5:lex.yy.c delete2.tab.c sym.cpp phase3.cpp phase4.cpp phase5.cpp
	$(CC) phase5.cpp -o run.out

de:lex.yy.c delete2.tab.c sym.cpp phase3.cpp phase4.cpp
	$(CC) -g lex.yy.c delete2.tab.c sym.cpp phase3.cpp phase4.cpp -o deCompile
	$(CC) -g phase5.cpp -o deRun
lex.yy.c: 
	flex delete.l

delete2.tab.c:
	bison -d delete2.y 

clean:
	rm -f *.c *.out *.h deRun deCompile *save *.bin

clean5: 
	rm -f  run.out


