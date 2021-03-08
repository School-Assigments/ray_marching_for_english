CFLAGS=-std=c++20 -fsanitize=address,undefined -march=native -Wall -Wextra -Wpedantic -O3 -g0 `libpng-config --cflags`
LDFLAGS=-std=c++20 -fsanitize=address,undefined `libpng-config --ldflags`

all: main.out

main.out: main.o
	g++ main.o $(LDFLAGS) -o main.out 

main.o: main.cpp settings.hpp vec.hpp
	g++ -c main.cpp -o main.o $(CFLAGS)

run: main.out
	./main.out
	feh output.png
