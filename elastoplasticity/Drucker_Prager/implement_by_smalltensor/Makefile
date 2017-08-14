# apex_stiffness_compile: dp.cpp apex_stiffness_main_test_dp.cpp
	# g++ apex_stiffness_main_test_dp.cpp dp.cpp -lm -std=c++11 -g -o test_dp
stiffness_compile:   dp.cpp stiffness_main_test_dp.cpp
	g++ stiffness_main_test_dp.cpp dp.cpp -lm -std=c++11 -g -o test_dp

# apex_compile:  dp.cpp main_test_dp_apex.cpp
# 	g++ main_test_dp_apex.cpp dp.cpp -lm -std=c++11 -g -o test_dp

compile: dp.cpp main_test_dp.cpp
	g++ main_test_dp.cpp dp.cpp -lm -std=c++11 -g -o test_dp

# run:
# 	script -c "./test_dp" log

# valgrind:
# 	valgrind ./test_dp

plot:
	python plot.py

clean:
	-rm test_dp
	-rm strain_stress.txt