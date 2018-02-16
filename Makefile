ALL = countwords
countwords: countwords.o
	gcc -o countwords countwords.o
countwords.o:
	gcc -c countwords.c -o countwords.o
clean:
	rm -f countwords.o countwords core *~
