
build:
	gcc -Wall -std=c99 ./src/*.c  -g  -o renderer -lSDL2 -lm


run:
	./renderer

clean:
	rm renderer


