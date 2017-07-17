CC = g++
DEBUG = -g -DDEBUG
CFLAGS = -Wall -std=c++11 $(DEBUG)
LFLAGS = -Wall -std=c++11 $(DEBUG)


basic_example: example.cpp ../src/ad_dual.cpp ../src/ad_graph.cpp
	$(CC) $(LFLAGS) -o example.out example.cpp ../src/ad_dual.cpp ../src/ad_graph.cpp

run_basic_example:
	./example.out

vector_dual: vector_dual.cpp ../src/ad_dual.cpp ../src/ad_graph.cpp
	$(CC) $(LFLAGS) -o vector_dual.out vector_dual.cpp ../src/ad_dual.cpp ../src/ad_graph.cpp

run_vector_dual:
	./vector_dual.out
		
clean:
	rm -f example.out
	rm -f vector_dual.out