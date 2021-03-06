///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// LTensor                                                                   //
//                                                                           //
// A Tensor Library with full Indicial Notation                              //
//                                                                           //
// Version 0.1                                                               //
// December 1, 2008                                                          //
//                                                                           //
// Copyright (C) 2007-2009-...                                               //
// Alejandro Limache & Sebastian Rojas Fredini                               //
//                                                                           //
// International Center of Computational Methods in Engineering  (CIMEC)     //
// Santa Fe, Argentina                                                       //
// alejandrolimache@gmail.com                                                //
//                                                                           //
// LTensor is freely available through the websites:                         //
// http://www.cimec.org.ar/alimache/                                         //
// http://code.google.com/p/ltensor/                                         //
// It may be copied, modified, and redistributed for non-commercial use as   // 
// long as the original authors and the Library get proper public credit     // 
// for its use.                                                              //
// Please consult the file LICENSE for the detailed copyright notices.       //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#ifndef Sum_TensorsRank1_H
#define Sum_TensorsRank1_H

#include "../../Promote_Types/promote.h"

///////////////////////////////////////////////
// Define SUM = A(i)+B(i)
///////////////////////////////////////////////



template < class A, class B, class T>
class Ai_plus_Bi
{

      private:

	const A  objA;
	const B  objB;

      public:

	~Ai_plus_Bi(){ }

	Ai_plus_Bi (const A &a, const B &b) : objA(a), objB(b)
	{
		#ifdef USE_ASSERT_Tensor_Operations
			assert (objA.get_dim1() == objB.get_dim1());
		#endif
	}

	inline T operator () (const int N1) const
	{
		return objA (N1) + objB (N1);
	}

	int get_dim1() const
	{
		return objA.get_dim1();
	}

	friend std::ostream & operator<< (std::ostream & os, const Ai_plus_Bi & v)
	{
		os << std::endl << "BEGIN:Ai_plus_Bi =" << &v << std::endl
		<< ", L = "<< (v.objA)
		<< ", R = " << (v.objB)
		<< "END.Ai_plus_Bi " << std::endl;
		return os;
	}
};

#endif
