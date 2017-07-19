#ifndef __types_H_
#define __types_H_

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cmath>

typedef int nodeID;





#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str ; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif    


#endif