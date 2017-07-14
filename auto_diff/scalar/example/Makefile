CC = g++
DEBUG = -g -DDEBUG
CFLAGS = -Wall -std=c++11 $(DEBUG)
LFLAGS = -Wall -std=c++11 $(DEBUG)


compile: example.cpp ../src/ad_dual.cpp ../src/ad_graph.cpp
	$(CC) $(LFLAGS) -o example.out example.cpp ../src/ad_dual.cpp ../src/ad_graph.cpp

run:
	./example.out

clean:
	rm -f example.out