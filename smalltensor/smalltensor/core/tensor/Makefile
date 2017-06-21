include_header_location=\
-I../../../third_party/libxsmm/build/include
link_lib_location=\
-L../../../third_party/libxsmm/build/lib
link_lib_name=\
-lxsmm \
-lxsmmext \
-lxsmmf \
-lxsmmgen \
-lxsmmnoblas \
-pthread \
-lblas \
-llapack \
-ldl

test_base:
	g++ test_tensor_order2.cpp -o test_tensor2 -std=c++11 ${include_header_location} ${link_lib_location} ${link_lib_name} -g

clean:
	rm -f test_tensor2