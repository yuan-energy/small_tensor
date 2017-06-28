## List of Supported Tensor Operations in small_tensor Library.

In the following, A, B, and C are order-1 to order-4 tensors and p is a scalar.
In addition, indices i, j, k, and l are free or dummy indices.

#### Tensor Multiply/Divide by a scalar
```cpp
A(i)       = p*B(i);
A(i,j)     = p*B(i,j);
A(i,j,k)   = p*B(i,j,k);
A(i,j,k,l) = p*B(i,j,k,l);
```

#### Tensor Summation/Subtraction
```cpp
A(i)       = B(i)+C(i);
A(i,j)     = B(i,j)+C(i,j);
A(i,j,k)   = B(i,j,k)+C(i,j,k);
A(i,j,k,l) = B(i,j,k,l)+C(i,j,k,l);
```

#### Tensor Condense
```cpp
p          = A(i,i);
A(i)       = B(i,j,j);
A(i,j)     = B(i,j,k,k);
```
<!-- A(i)  = B(j,i,j);
A(i)       = B(j,j,i);
A(i,j)     = B(k,k,i,j);
A(i,j)     = B(k,i,k,j);
A(i,j)     = B(k,i,j,k);
A(i,j)     = B(i,k,k,j);
A(i,j)     = B(i,k,j,k); -->
#### Tensor Outer Product
```cpp
A(i,j)     = B(i)*C(j);
A(i,j,k)   = B(i,j)*C(k);
A(i,j,k)   = B(i)*C(j,k);
A(i,j,k,l) = B(i,j,k)*C(l);
A(i,j,k,l) = B(i,j)*C(k,l);
A(i,j,k,l) = B(i)*C(j,k,l);
```

#### Tensor Contraction I (Dot Product)
```cpp
p          = A(i)*B(i);
A(i)       = B(i,j)*C(j); /*Need to fix*/
A(i)       = B(j)*C(i,j);
A(i,j)     = B(i,j,k)*C(k);
A(i,j)     = B(i,k)*C(k,j); /*This is actually matrix multiplication.*/
A(i,j)     = B(k)*C(k,i,j);
A(i,j,k)   = B(i,j,k,l)*C(l); 
A(i,j,k)   = B(i,j,l)*C(l,k);
A(i,j,k)   = B(i,l)*C(l,j,k);
A(i,j,k)   = B(l)*C(l,i,j,k);
A(i,j,k,l) = B(i,j,k,m)*C(m,l);
A(i,j,k,l) = B(i,j,m)*C(m,k,l);
A(i,j,k,l) = B(i,m)*C(m,j,k,l);
```

#### Tensor Contraction II (Double-Dot Product)
```cpp
p          = A(i,j)*B(i,j);
A(i)       = B(i,j,k)*C(j,k);
A(i)       = B(j,k)*C(j,k,i);
A(i,j)     = B(i,j,k,l)*C(k,l);
A(i,j)     = B(i,k,l)*C(k,l,j);
A(i,j)     = B(k,l)*C(k,l,i,j);
A(i,j,k)   = B(i,j,l,m)*C(l,m,k);
A(i,j,k)   = B(i,l,m)*C(l,m,j,k);
A(i,j,k,l) = B(i,j,m,n)*C(m,n,k,l);
```


The 36 operations above can be used together as well.







<br><br>
<br><br>
<br><br>
<br><br>
<br><br>
<br><br>
<br><br>
<br><br>
<br><br>
<br><br>





There are 32 tensor permutation operations listed below.
They are not used for the moment so they are NOT implemented.

#### Tensor Permutation
```cpp
A(i,j)     = B(i,j);
A(i,j)     = B(j,i);

A(i,j,k)   = B(i,j,k);
A(i,j,k)   = B(k,i,j);
A(i,j,k)   = B(j,k,i);
A(i,j,k)   = B(i,k,j);
A(i,j,k)   = B(j,i,k);
A(i,j,k)   = B(k,j,i);

A(i,j,k,l) = B(i,j,k,l);
A(i,j,k,l) = B(i,j,l,k);
A(i,j,k,l) = B(i,k,j,l);
A(i,j,k,l) = B(i,k,l,j);
A(i,j,k,l) = B(i,l,j,k);
A(i,j,k,l) = B(i,l,k,j);

A(i,j,k,l) = B(j,i,l,k);
A(i,j,k,l) = B(j,i,k,l);
A(i,j,k,l) = B(j,k,i,l);
A(i,j,k,l) = B(j,k,l,i);
A(i,j,k,l) = B(j,l,i,k);
A(i,j,k,l) = B(j,l,k,i);

A(i,j,k,l) = B(k,i,j,l);
A(i,j,k,l) = B(k,i,l,j);
A(i,j,k,l) = B(k,j,i,l);
A(i,j,k,l) = B(k,j,l,i);
A(i,j,k,l) = B(k,l,i,j);
A(i,j,k,l) = B(k,l,j,i);

A(i,j,k,l) = B(l,i,j,k);
A(i,j,k,l) = B(l,i,k,j);
A(i,j,k,l) = B(l,j,i,k);
A(i,j,k,l) = B(l,j,k,i);
A(i,j,k,l) = B(l,k,i,j);
A(i,j,k,l) = B(l,k,j,i);
```
