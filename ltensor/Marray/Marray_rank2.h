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
// -*- c++ -*-
#ifndef Marray_rank2_H
#define Marray_rank2_H

//#define USE_ASSERT_Marray
#ifdef USE_ASSERT_Marray
#include <assert.h>
#endif

#define CHECK										\
	assert( (n1<get_dim1())&& (n2<get_dim2()) );	\
	assert( (n1>=0) && (n2>=0));


//#define CHECK_Marray_rank2


#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include "../algorithms/algorithms.h"

#include "../Tensor_Operations/Tensor_Operations.h"
#include "../Expr/Expr1/Expr1s.h"
#include "../Expr/Expr2/Expr2s.h"


/* DGESV prototype */
// extern void dgesv_( int* n, int* nrhs, double* a, int* lda, int* ipiv,
//                     double* b, int* ldb, int* info );

#ifdef _LTENSOR_HAVE_CLAPACK
extern "C" {
#include <clapack.h>
}
#endif

template < class A, class T, char i > class Expr1;
template < class A, class T, char i, char j > class Expr2;
template < class A, class T> class F_Expr2;



#define rank 2

//
// FUNTIONS DECLARATIONS in order to FRIEND Function "ostream <<"  to work
//
template < class T, class base> class Marray <T, rank, base>;

template<class T, class base>
std::ostream & operator << (std::ostream & os, const Marray<T, rank, base> & v);

//
// Class Definition
//
template < class T, class base>
class Marray <T, rank, base> : public base
{


    ////////////////
    //Constructors
    ///////////////
public:



    Marray (long dimension1, long dimension2): base(dimension1, dimension2)
    {
        (*this) = (T)0.0;

    }

    Marray (long dimension1, long dimension2, T valor): base(dimension1, dimension2)
    {
        *this = valor;
    }

    Marray(long dimension1, long dimension2, std::string type): base(dimension1, dimension2)
    {
        if (type == "identity")
        {
            this->Identity();
        }
        else
        {
            std::cerr << "Marray (rank 2) -- Unknown type " << type << ". Defaulting to zero!!\n" << std::endl;
            *this = (T)0.0;
        }
    };

    Marray()
    {
    };



    template <class fType, class b>
    Marray<T, rank, base>& operator=(const Marray<fType, rank, b> &rterm)
    {
        //	   //make sure sizes are compatible
        //	   //base::equals(*dynamic_cast<base*>(const_cast<Marray<T,rank,base>*> (&rterm)) );
        //// 	    #ifdef CHECK_OOB
        //// 	    assert( (get_dim1() !=0 ) && (get_dim2()!=0));
        //// 	    #endif
        //	resize(rterm.get_dim1(),rterm.get_dim2());
        //		for(int i=0;i<get_dim1();i++)
        //			for(int j=0;j<get_dim2();j++)
        //			(*this)(i,j)=rterm(i,j);
        base::operator=(*dynamic_cast<const b*>(&rterm));
        return *this;
    }

    Marray<T, rank, base>& operator=(const Marray<T, rank, base> &rterm)
    {
        //make sure sizes are compatible
        //base::equals(*dynamic_cast<base*>(const_cast<Marray<T,rank,base>*> (&rterm)) );
        //resize(rterm.get_dim1(),rterm.get_dim2());
        //for(int i=0;i<get_dim1();i++)
        //	for(int j=0;j<get_dim2();j++)
        //	(*this)(i,j)=rterm(i,j);
        base::operator=(*dynamic_cast<const base*>(&rterm));
        return *this;

    }

    template <class A, class U>
    Marray<T, rank, base>& operator=(const F_Expr2 < A, U> &expr)
    {

        for (int i = 0; i < expr.get_dim1(); i++)
            for (int j = 0; j < expr.get_dim1(); j++)
            {
                (*this)(i, j) = expr(i, j);
            }


        return (*this);
    }

    template <class U>
    inline Marray<T, rank, base> & operator= (const U &u)
    {
        for ( int i = 0; i < get_dim1(); i++)
            for (int j = 0; j < get_dim2(); j++)
            {
                (*this)(i, j) = u;
            }
        return *this;

    }

    template <class U>
    inline Marray<T, rank, base> & operator+= (const U &u)
    {
        for ( int i = 0; i < get_dim1(); i++)
            for (int j = 0; j < get_dim2(); j++)
            {
                (*this)(i, j) += u;
            }
        return *this;

    }

    template <class U>
    inline Marray<T, rank, base> & operator-= (const U &u)
    {
        for ( int i = 0; i < get_dim1(); i++)
            for (int j = 0; j < get_dim2(); j++)
            {
                (*this)(i, j) -= u;
            }
        return *this;

    }


    template <class U>
    inline Marray<T, rank, base> & operator*= (const U &u)
    {
        for ( int i = 0; i < get_dim1(); i++)
            for (int j = 0; j < get_dim2(); j++)
            {
                (*this)(i, j) *= u;
            }
        return *this;

    }


    template <class U>
    inline Marray<T, rank, base> & operator/= (const U &u)
    {
        for ( int i = 0; i < get_dim1(); i++)
            for (int j = 0; j < get_dim2(); j++)
            {
                (*this)(i, j) /= u;
            }
        return *this;

    }

    //#else
    //	using base::operator=;
    //#endif


    Marray(long* dimensions): base(dimensions)
    {
        (*this) = 0;
    }


    //copy constructor
    Marray(const Marray<T, rank, base> &R)
    {
        (*this) = R;
    }

    void sucesion(int init, int stride = 1)
    {
        int count = init;
        for (int i = 0; i < get_dim1(); i++)
        {
            for (int j = 0; j < get_dim2(); j++)
            {
                (*this)(i, j) = count;
                count = count + stride;
            }
        }
    }
    inline const T operator() (const int n1, const int n2) const
    {
#ifdef CHECK_OOB
        CHECK
#endif
        return base::operator()(n1, n2);

    }

    inline T & operator() (const int n1, const int n2)
    {
#ifdef CHECK_OOB
        CHECK
#endif
        return base::operator()(n1, n2);
    }


    //////////////////////////////////////////////////////////////
    // MEMBER FUNCTIONS
    //////////////////////////////////////////////////////////////



    void resize(long d1, long d2)
    {
        unsigned long  dim[2];
        dim[0] = d1;
        dim[1] = d2;
        base::resize(dim);
        (*this) = (T)0;

    }

    inline int get_size() const
    {

        return base::size[0] * base::size[1];

    }


    inline int get_dim1() const
    {
        return base::size[0];

    }

    inline int get_dim2() const
    {
        return base::size[1];
    }

    inline void show_shape()
    {
        std::cout << base::size[0] << "x" << base::size[1] << std::endl;
    };

    void inline operator=(const char *data)
    {

        char delim;
        std::stringstream stream;
        stream << data;

        for (int i = 0; i < get_dim1(); i++)
        {
            for (int j = 0; j < get_dim2(); j++)
            {
                stream >> (*this)(i, j);
            }
            stream >> delim;
            assert(delim == ';');
        }





    }

    friend std::ostream & operator << <T>
    (std::ostream & os, const Marray<T, rank, base> & v);

private:
    //end FExpres

    template < char i, char j , int iType1, int iType2>
    inline Expr2 < Encapsulate_to_Expr2<Marray<T, rank, base>, T, rank, 12, Index<i, iType1>, Index<j, iType2> >, T, i , j >
    operator() (const Index < i , iType1> & index1, const Index < j , iType2> & index2)
    {

        typedef Encapsulate_to_Expr2<Marray<T, rank, base>, T, rank, 12, Index<i, iType1> , Index <j, iType2 > >Expr_Obj;
        return Expr2<Expr_Obj, T, i, j>(Expr_Obj(*this, index1, index2));
    }

    template < char i, char j , int iType1, int iType2>
    inline Expr2 < Encapsulate_to_Expr2<const Marray<T, rank, base>, T, rank, 12, Index<i, iType1>, Index<j, iType2> >, T, i , j >
    operator() (const Index < i , iType1> & index1, const Index <j , iType2> & index2)const
    {

        typedef Encapsulate_to_Expr2<const Marray<T, rank, base>, T, rank, 12, Index<i, iType1> , Index <j, iType2 > >Expr_Obj;
        return Expr2<Expr_Obj, T, i, j>(Expr_Obj(*this, index1, index2));
    }

    //checked


    template < char i, int iType1>
    inline Expr1 < Encapsulate_to_Expr1<Marray<T, rank, base>, T, rank, 1, Index<i, iType1> >, T, i>
    operator() (const Index < i, iType1 > & index1, const int N)
    {
        typedef Encapsulate_to_Expr1<Marray<T, rank, base>, T, rank, 1, Index<i, iType1> > Expr_Obj;
        return Expr1<Expr_Obj, T, i>(Expr_Obj(*this, N, index1));
    }

    template < char i, int iType1>
    inline Expr1 < Encapsulate_to_Expr1<const Marray<T, rank, base>, T, rank, 1, Index<i, iType1> >, T, i>
    operator() (const Index < i, iType1 > & index1, const int N)const
    {
        typedef Encapsulate_to_Expr1<const Marray<T, rank, base>, T, rank, 1, Index<i, iType1> > Expr_Obj;
        return Expr1<Expr_Obj, T, i>(Expr_Obj(*this, N, index1));
    }


    //checked

    template < char i, int iType2>
    inline Expr1 < Encapsulate_to_Expr1<Marray<T, rank, base>, T, rank, 2, Index<i, iType2> >, T, i>
    operator() (const int N, const Index < i, iType2 > & index2 )
    {
        typedef Encapsulate_to_Expr1<Marray<T, rank, base>, T, rank, 2, Index<i, iType2> > Expr_Obj;
        return Expr1<Expr_Obj, T, i>(Expr_Obj(*this, N, index2));
    }

    template < char i, int iType2>
    inline Expr1 < Encapsulate_to_Expr1<const Marray<T, rank, base>, T, rank, 2, Index<i, iType2> >, T, i>
    operator() (const int N, const Index < i, iType2 > & index2 )const
    {
        typedef Encapsulate_to_Expr1<const Marray<T, rank, base>, T, rank, 2, Index<i, iType2> > Expr_Obj;
        return Expr1<Expr_Obj, T, i>(Expr_Obj(*this, N, index2));
    }

    //checked

    template < char i , int iType1, int iType2>
    inline T  operator() (const Index < i, iType1 > & index1, const Index < i, iType2 > & index2)
    {
        T res = 0;
        for (int n1 = 0; n1 < get_dim1(); ++n1)
        {
            res += (*this)(n1, n1);
        }
        return res;
    }

    template < char i , int iType1, int iType2>
    inline T  operator() (const Index < i, iType1 > & index1, const Index < i, iType2 > & index2) const
    {
        T res = 0;
        for (int n1 = 0; n1 < get_dim1(); ++n1)
        {
            res += (*this)(n1, n1);
        }
        return res;
    }

    /////////////////////////////////////////////////////////////
    // Assignation Operations from other Marray<T,rank,base> object
    /////////////////////////////////////////////////////////////

    template <class U, class base2>
    inline Marray<T, rank, base> & operator+= (const Marray<U, rank, base2> & a)
    {
        for (int i = 0; i < get_dim1(); i++)
        {
            for (int j = 0; j < get_dim2(); j++)
            {
                (*this)(i, j) += a(i, j);
            }
        }
        return *this;
    }



    //Implemented for compatibility only, shouldn't be used in performance critic sections
    //will fix this with the new cxx specification

    inline Marray<T, rank, base> operator-()
    {

        Marray<T, rank, base> temp(get_dim1(), get_dim2());

        for (int i = 0; i < get_dim1(); i++)
        {
            for (int j = 0; j < get_dim2(); j++)
            {
                temp(i, j) = -(*this)(i, j);
            }
        }

        return temp;
    }



    //Compatibily operators
    //cstyle ordering

    template <class Type>
    void fromCArray(Type * datos, int dim1, int dim2)
    {
        resize(dim1, dim2);

        for (int i = 0; i < dim1; i++)
            for (int j = 0; j < dim2; j++)
            {
                (*this)(i, j) = datos[i * dim1 + j];
            }
    }

    template <class Type>
    void toCArray(Type * datos)
    {


        int dim1 = get_dim1();
        int dim2 = get_dim2();
        for (int i = 0; i < dim1; i++)
            for (int j = 0; j < dim2; j++)
            {
                datos[i * dim1 + j] = (*this)(i, j);
            }
    }

    template <class U, class base2>
    inline Marray<T, rank, base> & operator-= (const Marray<U, rank, base2> & a)
    {
        for (int i = 0; i < get_dim1(); i++)
        {
            for (int j = 0; j < get_dim2(); j++)
            {
                (*this)(i, j) -= a(i, j);
            }
        }
        return *this;
    }

    bool operator==(const Marray<T, rank, base> &a)
    {
        if (get_dim1() != a.get_dim1())
        {
            return false;
        }
        if (get_dim2() != a.get_dim2())
        {
            return false;
        }

        for (int i = 0; i < get_dim1(); i++)
        {
            for (int j = 0; j < get_dim2(); j++)
            {

                if ( (*this)(i, j) != a(i, j))
                {
                    return false;
                }
            }

        }
        return true;

    }





template <class Type, class base>
std::ostream & operator<< (std::ostream & os, const  Marray<Type, rank, base> & v)
{
    std::cout << "MArray2[" << v.get_dim1() << "," << v.get_dim2() << "] = " << std::endl << "\t[ " << std::endl;

    if ((v.get_dim1()*v.get_dim2()) > 0)
    {
        for ( int i = 0; i < v.get_dim1(); i++)
        {
            for (int j = 0; j < v.get_dim2(); j++)
            {
                std::cout << std::setw(10) << std::setprecision(5) << v(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }
    std::cout << "\t]" << std::endl;

    return os;
}
#undef CHECK
#undef rank

#endif

