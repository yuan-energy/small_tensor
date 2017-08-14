#include "../../smalltensor::ad/app/smalltensor.h"
// ad_graph<double> GRAPH;

// stress3D tensor2<double, 3, 3> obj1;

// using namespace smalltensor::ad;

// namespace smalltensor{
// 	namespace ad{
// 		template<typename __dat_t>
// 		class tensor2<__dat_t, 3, 3>
// 		{
// 			typedef tensor2<__dat_t, 3, 3> stress3D;
// 		public:
// 			__dat_t getI1() const{
// 				__dat_t ret(*((*this)(0,0)._graph), 0.) ;
// 				for (std::size_t n1 = 0; n1 < 3; ++n1){
// 					ret = ret + (*this)(n1,n1);
// 				}
// 				return ret;
// 			}
// 		};
// 	}
// }


