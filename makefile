all: pipe.c
	gcc -o run pipe.c

run: all
	./run

clean: 
	rm run
	rm a.out