include_header_location=\
# -I../../
link_lib_location=\
# -L../../
link_lib_name=\
# -pthread \
# -lblas \
# -llapack \
# -ldl

test_base:
	g++ test_tensor2.cpp -o test_tensor2 -std=c++11 ${include_header_location} ${link_lib_location} ${link_lib_name} -g

test_by_clang:
	clang++ test_tensor2.cpp -o test_tensor2 -std=c++11 ${include_header_location} ${link_lib_location} ${link_lib_name} -g

clean:
	rm -f test_tensor2
