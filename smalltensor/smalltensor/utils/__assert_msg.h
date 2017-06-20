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