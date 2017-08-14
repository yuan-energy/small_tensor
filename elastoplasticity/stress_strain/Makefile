
OBJS = *.o
CC = g++
DEBUG = -g -DDEBUG
CFLAGS = -Wall -std=c++11 $(DEBUG)
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

stress3D:
	$(CC) $(CFLAGS) test.cpp -o test.out ${INCLUDE_HEADER_LOCATION} ${LINK_LIB_LOCATION} ${LINK_LIB_NAME}