CC = g++
CFLAGS = -Wall -Wextra -g
LDFLAGS =

SRCS = $(wildcard cpp/*.cpp)
OBJS = $(SRCS:cpp/%.cpp=o/%.o)

.PHONY: all clean

all: o/ jogo_epico

jogo_epico: $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@ -lm -lraylib

o/main.o: cpp/main.cpp
	$(CC) $(CFLAGS) -c $< -o $@

o/%.o: cpp/%.cpp hpp/%.hpp
	$(CC) $(CFLAGS) -c $< -o $@

o/:
	mkdir $@

clean:	
	rm -rf jogo_epico o/
