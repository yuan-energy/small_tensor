#pragma once
#include "../utils/__utils.h"
namespace smalltensor
{
	namespace ad{
		#include "../src/autodiff/ad_dual.hpp"
		#include "../src/autodiff/ad_graph.hpp"
		#include "../src/autodiff/ad_dual_operations.h"
		#include "../src/tensors/tensors.h"
		#include "../src/expressions/expressions.h"
		#include "../src/operations/operations.h"
		
		// typedef tensor1<double,3> VECT3 ;
		typedef tensor2<ad_dual<double>,3,3> ADtensor2 ;
		typedef tensor4<ad_dual<double>,3,3,3,3> ADtensor4 ;
	}
}





