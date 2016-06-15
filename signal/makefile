
OBJ = signal.o

resultat:$(OBJ) main.o
	gcc -Wall -std=gnu99 $(OBJ) main.o -o res.exe


main.o:$(OBJ)
	gcc -Wall main.c -c
signal.o:
	gcc -Wall signal.c -c

clean:
	rm *~
	rm *.o
	rm *.exe


