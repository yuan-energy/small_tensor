#ifndef SMALL_TENSOR_SMALLTENSOR_INTRINSIC_H_
#define SMALL_TENSOR_SMALLTENSOR_INTRINSIC_H_


#include "src/tensors/tensors.h"
#include "src/expressions/expressions.h"
#include "src/operations/operations.h"

typedef smalltensor::tensor1<double,3> VECT3 ;
typedef smalltensor::tensor2<double,3,3> stresstensor ;
typedef smalltensor::tensor2<double,3,3> straintensor ;
typedef smalltensor::tensor4<double,3,3,3,3> stifftensor ;


#endif // SMALL_TENSOR_SMALLTENSOR_INTRINSIC_H_
