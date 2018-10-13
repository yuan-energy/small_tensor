
OBJS = test_tensor1.o test_tensor2.o test_tensor3.o test_tensor4.o
CC = g++
DEBUG = -g -DDEBUG
CFLAGS = -Wall -std=c++11 -march=native $(DEBUG)
LFLAGS = -Wall -std=c++11 $(DEBUG)

INCLUDE_HEADER_LOCATION=\
# -I../../
LINK_LIB_LOCATION=\
# -L../../
LINK_LIB_NAME=\
# -pthread \
# -lblas \
# -llapack \
# -ldl

all: compile_all run_all

compile_all: test_tensor1 test_tensor2 test_tensor3 test_tensor4
test_tensor1:
	$(CC) $(CFLAGS) test_tensor1.cpp -o test_tensor1.out  ${INCLUDE_HEADER_LOCATION} ${LINK_LIB_LOCATION} ${LINK_LIB_NAME}
test_tensor2:
	$(CC) $(CFLAGS) test_tensor2.cpp -o test_tensor2.out  ${INCLUDE_HEADER_LOCATION} ${LINK_LIB_LOCATION} ${LINK_LIB_NAME}
test_tensor3:
	$(CC) $(CFLAGS) test_tensor3.cpp -o test_tensor3.out  ${INCLUDE_HEADER_LOCATION} ${LINK_LIB_LOCATION} ${LINK_LIB_NAME}
test_tensor4:
	$(CC) $(CFLAGS) test_tensor4.cpp -o test_tensor4.out  ${INCLUDE_HEADER_LOCATION} ${LINK_LIB_LOCATION} ${LINK_LIB_NAME}

run_all: run_tensor1 run_tensor2 run_tensor3 run_tensor4
run_tensor1:
	./test_tensor1.out
run_tensor2:
	./test_tensor2.out
run_tensor3:
	./test_tensor3.out
run_tensor4:
	./test_tensor4.out
clean:
	rm -f test_tensor1.out
	rm -f test_tensor2.out
	rm -f test_tensor3.out
	rm -f test_tensor4.out
