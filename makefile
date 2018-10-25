all: main
main: echo pwd cp sort
echo: echo.c
	gcc -g -o echo echo.c
pwd: pwd.c
	gcc -g -o pwd pwd.c
cp: cp.c
	gcc -g -o cp cp.c
sort: sort.c
	gcc -g -o sort sort.c
clean:
	rm echo pwd cp sort