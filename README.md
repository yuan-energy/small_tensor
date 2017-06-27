### Small Tensor Library

This is a small tensor library which supports full Einstein notations. 

#### Why this library might be useful to you

To do fast tensor operations, one needs to write them in C/Fortran code style for performance. This means that one needs to use several "for loops" in order to do the products and sums component-wise. 

Although computationally efficient, this type of programming style is error prone and makes codes lenghtier and hard to be debugged.

With small tensor library, we get the performance of a C code style combined with the code clarity and simplicity given by indicial tensor notation.

To perform tensor operations with small-tensor, one just needs to write in the .cpp the following "exactly replicate" code:

```cpp
Index<'i'> i; Index<'j'> j; Index<'k'> k; Index<'l'> l;
```

A double contraction of a 4th-order tensor stiffness with a 2nd-order tensor strain can be written simply as:
```cpp
sigma(i,j)=stiffness(i,j,k,l)*strain(k,l);
```

#### Small Tensor without heap memory in Runtime. 
Simple usage example for 3 by 3 matrix:
```cpp
tensor2<double,3,3> stress;
```
This is useful is either of the following cases:

* Avoid the malloc in the runtime.
* Since the data is kept in-place, you can save extra cache miss in the common case.


#### Development Status 
This repository is under development. This is the basic version.
The next steps:

* Asynchronous computation Future/Promise or Concunrrent Queue.
* Batch the small tensors.
* Enable GPUs.
* Use fewer multiplication by PCA for isotropic tensors.