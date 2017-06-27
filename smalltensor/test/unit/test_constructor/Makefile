include_header_location=\
# -I../../
link_lib_location=\
# -L../../
link_lib_name=\
# -pthread \
# -lblas \
# -llapack \
# -ldl

all: compile_all run_all

compile_all: test_tensor1 test_tensor2 test_tensor3 test_tensor4
test_tensor2:
	g++ test_tensor2.cpp -DDEBUG -o test_tensor2 -std=c++11 ${include_header_location} ${link_lib_location} ${link_lib_name} -g

test_tensor2_by_clang:
	clang++ test_tensor2.cpp -DDEBUG -o test_tensor2 -std=c++11 ${include_header_location} ${link_lib_location} ${link_lib_name} -g


test_tensor1:
	g++ test_tensor1.cpp -DDEBUG -o test_tensor1 -std=c++11 ${include_header_location} ${link_lib_location} ${link_lib_name} -g
test_tensor3:
	g++ test_tensor3.cpp -DDEBUG -o test_tensor3 -std=c++11 ${include_header_location} ${link_lib_location} ${link_lib_name} -g
test_tensor4:
	g++ test_tensor4.cpp -DDEBUG -o test_tensor4 -std=c++11 ${include_header_location} ${link_lib_location} ${link_lib_name} -g

run_all: run_tensor1 run_tensor2 run_tensor3 run_tensor4

run_tensor1:
	./test_tensor1
run_tensor2:
	./test_tensor2
run_tensor3:
	./test_tensor3
run_tensor4:
	./test_tensor4
clean:
	rm -f test_tensor1
	rm -f test_tensor2
	rm -f test_tensor3
	rm -f test_tensor4
