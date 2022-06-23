LCS.o: extractlcs.c extractlcs.h
	gcc -c extractlcs.c
main.o: main.c
	gcc -c main.c
start: main.o LCS.o
	gcc -o start main.o extractlcs.o
all: start
rm:
	rm main.o LCS.o start
