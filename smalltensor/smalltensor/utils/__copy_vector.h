#ifndef __COPY_VECTOR_H_
#define __COPY_VECTOR_H_
template <typename T>
inline void copy_vector(T* v1,T* v2,int n){
    for(int i=0;i<n;i++)
        v1[i]=v2[i];
    }

template <typename T1, typename T2>
inline void copy_vector(T1* v1,T2* v2,int n){
    for(int i=0;i<n;i++)
        v1[i]=static_cast<T1>(v2[i]);
    }
#endif /*__COPY_VECTOR_H_*/