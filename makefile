all: echo pwd cp sort tail
echo: echo.c
	gcc -g -o echo echo.c
pwd: pwd.c
	gcc -g -o pwd pwd.c
cp: cp.c
	gcc -g -o cp cp.c
tail: tail.o help.o str_list.o
	gcc -g help.o tail.o str_list.o -o tail
sort: sort.o help.o str_list.o
	gcc -g str_list.o help.o sort.o -o sort
tail.o: tail.c help.h
	gcc -c tail.c
sort.o: sort.c
	gcc -c sort.c
help.o: help.c help.h sh.h
	gcc -c help.c
str_list.o: str_list.c sh.h
	gcc -c str_list.c
clean:
	rm echo pwd cp sort tail *.o