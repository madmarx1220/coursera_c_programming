mytest: cards.o deck.o input.o future.o main.o
	gcc -o mytest -ggdb3 cards.o deck.o input.o future.o main.o
main.o: main.c
	gcc -ggdb3 -std=gnu99 -pedantic -Wall -c main.c
cards.o: cards.c
	gcc -ggdb3 -std=gnu99 -pedantic -Wall -c cards.c
deck.o: deck.c
	gcc -ggdb3 -std=gnu99 -pedantic -Wall -c deck.c
input.o: input.c
	gcc -ggdb3 -std=gnu99 -pedantic -Wall -c input.c
future.o: future.c
	gcc -ggdb3 -std=gnu99 -pedantic -Wall -c future.c
