CC=clang
FLAGS=-Wall -Werror -Wpedantic -ggdb
STD=c11
LINK=-lpthread -lm

CCA=$(CC) $(FLAGS) -std=$(STD) $(LINK)

compile: src/main.c
	$(CCA) src/main.c src/server.c build/mnl.a -o build/client.out
run:
	build/client.out
