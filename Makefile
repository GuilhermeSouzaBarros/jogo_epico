CC = g++
CFLAGS = -Wall -Wextra -g
LDFLAGS =

SRCS = $(wildcard cpp/*.cpp)
OBJS = $(SRCS:cpp/%.cpp=o/%.o)

.PHONY: all clean

all: jogo_epico

jogo_epico: $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@ -lm -lraylib

o/:
	mkdir o/

o/main.o: cpp/main.cpp o/
	$(CC) $(CFLAGS) -c $< -o $@

o/%.o: cpp/%.cpp hpp/%.hpp o/
	$(CC) $(CFLAGS) -c $< -o $@

clean:	
	rm -f jogo_epico $(OBJS)
