CC = g++
DEBUG = -g -DDEBUG
CFLAGS = -Wall -std=c++11 $(DEBUG)
LFLAGS = -Wall -std=c++11 $(DEBUG)

INCLUDE_HEADER_LOCATION=\
-I../../../../../include/
LINK_LIB_LOCATION=\
# -L../../
LINK_LIB_NAME=\
# -pthread \
# -lblas \
# -llapack \
# -ldl

all: apex_stiffness_compile stiffness_compile apex_compile compile

apex_stiffness_compile: DruckerPragerPerfectlyPlastic.cpp apex_stiffness_main_test_dp.cpp
	g++ apex_stiffness_main_test_dp.cpp DruckerPragerPerfectlyPlastic.cpp \
		-lm -std=c++11 -g -o test_dp.out \
		$(INCLUDE_HEADER_LOCATION)
	
stiffness_compile:   DruckerPragerPerfectlyPlastic.cpp stiffness_main_test_dp.cpp
	g++ stiffness_main_test_dp.cpp DruckerPragerPerfectlyPlastic.cpp \
		-lm -std=c++11 -g -o test_dp.out \
		$(INCLUDE_HEADER_LOCATION)

apex_compile:  DruckerPragerPerfectlyPlastic.cpp main_test_dp_apex.cpp
	g++ main_test_dp_apex.cpp DruckerPragerPerfectlyPlastic.cpp \
	-lm -std=c++11 -g -o test_dp.out \
	$(INCLUDE_HEADER_LOCATION)

compile: DruckerPragerPerfectlyPlastic.cpp main_test_dp.cpp
	g++ main_test_dp.cpp DruckerPragerPerfectlyPlastic.cpp \
	-lm -std=c++11 -g -o test_dp.out \
	$(INCLUDE_HEADER_LOCATION)

run: 
	# g++ stiffness_main_test_dp.cpp DruckerPragerPerfectlyPlastic.cpp -lm -std=c++11 -g -o test_dp
	script -c "./test_dp.out" log

# valgrind:
# 	valgrind ./test_dp

plot:
	python plot.py

clean:
	-rm test_dp
	-rm strain_stress.txt