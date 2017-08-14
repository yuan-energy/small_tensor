files=./*


find . -type f -name "*.h" -exec sed -e "/#include\ <assert\.h>/d" -i {} \;
find . -type f -name "*.h" -exec sed -e "/#include\ <iostream>/d" -i {} \;
find . -type f -name "*.h" -exec sed -e "/#include\ <algorithm>/d" -i {} \;
find . -type f -name "*.h" -exec sed -e "/#include\ <cassert>/d" -i {} \;
find . -type f -name "*.h" -exec sed -e "/#include\ <cstdarg>/d" -i {} \;
find . -type f -name "*.h" -exec sed -e "/#include\ <string>/d" -i {} \;
find . -type f -name "*.h" -exec sed -e "/#include\ <iomanip>/d" -i {} \;
find . -type f -name "*.h" -exec sed -e "/#include\ <fstream>/d" -i {} \;
find . -type f -name "*.h" -exec sed -e "/#include\ <sstream>/d" -i {} \;
find . -type f -name "*.h" -exec sed -e "/#include\ <vector>/d" -i {} \;
find . -type f -name "*.h" -exec sed -e "/#include\ <cmath>/d" -i {} \;
find . -type f -name "*.h" -exec sed -e "/#include\ <cstdlib>/d" -i {} \;
find . -type f -name "*.h" -exec sed -e "/#include\ <stdio\.h>/d" -i {} \;
find . -type f -name "*.h" -exec sed -e "/#include\ <sys\/param\.h>/d" -i {} \;
find . -type f -name "*.h" -exec sed -e "/#include\ <sys\/times\.h>/d" -i {} \;
find . -type f -name "*.h" -exec sed -e "/#include\ <sys\/types\.h>/d" -i {} \;
find . -type f -name "*.h" -exec sed -e "/#include\ <sys\/time\.h>/d" -i {} \;
find . -type f -name "*.h" -exec sed -e "/#include\ <ctime\>/d" -i {} \;


#include <stdio.h>
#include <sys/param.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/time.h>
#include <ctime>




# sed -e "/#include\ <assert\.h>/d" -i Expr4_minus_Expr4.h 