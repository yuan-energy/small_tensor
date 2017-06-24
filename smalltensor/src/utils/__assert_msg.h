#ifndef __ASSERT_MSG_H_
#define __ASSERT_MSG_H_
    #ifndef NDEBUG
    #   define ASSERT_MSG(condition, message) \
        do { \
            if (! (condition)) { \
                std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                          << " line " << __LINE__ << ": \nError!!! " << message << std::endl; \
                std::terminate(); \
            } \
        } while (false)
    #else
    #   define ASSERT_MSG(condition, message) do { } while (false)
    #endif
#endif /*__ASSERT_MSG_H_*/