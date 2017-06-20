#include <cstdio>
#include <iostream>

#ifndef NDEBUG
#   define assert_msg(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": \n" << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#   define assert_msg(condition, message) do { } while (false)
#endif


int main(int argc, char const *argv[])
{
	assert_msg(2+2 == 4, "ERROR!!: 2+2==4 ") ;
	assert_msg(2+2 == 5, "ERROR!!: 2+2==5 ") ;
	return 0;
}