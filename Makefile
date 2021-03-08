CFLAGS=-std=c++20 -fsanitize=address,undefined -march=native -Wall -Wextra -Wpedantic -O3 -g0 `libpng-config --cflags`
LDFLAGS=-std=c++20 -fsanitize=address,undefined `libpng-config --ldflags`

all: main.out

main.out: main.o vec.o map.o
	g++ main.o vec.o map.o $(LDFLAGS) -o main.out 

main.o: main.cpp settings.hpp
	g++ -c main.cpp -o main.o $(CFLAGS)

vec.o: vec.cpp vec.hpp
	g++ -c vec.cpp -o vec.o $(CFLAGS)

map.o: map.cpp map.hpp
	g++ -c map.cpp -o map.o $(CFLAGS)

run: main.out
	./main.out
	feh output.png
