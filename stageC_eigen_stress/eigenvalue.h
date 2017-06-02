#include <math.h>
#include <vector>
#include "../ltensor/LTensor.h"
using namespace std;

double trace(DTensor2 const& MAT){
   return MAT(0,0) + MAT(1,1) + MAT(2,2) ; 
}
Index<'i'> _i;
Index<'j'> _j;
Index<'k'> _k;
Index<'l'> _l;
Index<'m'> _m;
Index<'n'> _n;

const DTensor2 kronecker_delta(3, 3, "identity");
const double pi = 3.1415926535897932384626433832795028841971693993 ; 

double det(DTensor2 const& matA){
   DTensor2 matC(3,3,0.); 
   matC = matA; 
   return matC(0,0) * (matC(1,1)*matC(2,2) - matC(1,2)*matC(2,1)) 
        - matC(0,1) * (matC(1,0)*matC(2,2) - matC(1,2)*matC(2,0))
        + matC(0,2) * (matC(1,0)*matC(2,1) - matC(1,1)*matC(2,0));
}

vector<double> const& eigenvalues(DTensor2 const& MAT)
{
   double p1 = pow(MAT(0,1),2) + pow(MAT(0,2),2) + pow(MAT(1,2),2) ; 
   double eig1,eig2,eig3;
   if (p1 == 0) {
      // % MAT is diagonal.
      eig1 = MAT(0,0);
      eig2 = MAT(1,1);
      eig3 = MAT(2,2);
      return vector<double>({eig1,eig2,eig3}) ; 
   }
   double q = trace(MAT)/3. ; 
   double p2 = pow((MAT(0,0) - q),2) + pow((MAT(1,1) - q),2) + pow((MAT(2,2) - q),2) + 2 * p1  ; 
   double p = sqrt(p2 / 6.)  ; 
   DTensor2 matB(3,3,0.) ; 
   matB(_i,_j) = (1. / p) * (MAT(_i,_j) - q * kronecker_delta(_i,_j) )       ;   // I is the identity matrix
   double r = det(matB) / 2.  ; 

   // % In exact arithmetic for a symmetric matrix  -1 <= r <= 1
   // % but computation error can leave it slightly outside this range.
   double phi ; 
   if (r <= -1) 
      phi = pi / 3. ; 
   else if (r >= 1)
      phi = 0 ; 
   else
      phi = acos(r) / 3. ; 

   // % the eigenvalues satisfy eig3 <= eig2 <= eig1
   eig1 = q + 2 * p * cos(phi)   ; 
   eig3 = q + 2 * p * cos(phi + (2*pi/3.))   ; 
   eig2 = 3 * q - eig1 - eig3     ;    // since trace(MAT) = eig1 + eig2 + eig3

   return vector<double>({eig1,eig2,eig3}) ; 
}


DTensor2 const& eigenvector(DTensor2 const& MAT, vector<double> const& eigenvalues)
{
   DTensor2 eig_vecs(3,3,0.) ; 
   // eig_vec1 
   vector<double> v1(3,0.), v2(3,0.);
   v1(0) = MAT(0,0) - eigenvalues[0] ; 
   v1(1) = MAT(1,0) ;
   v1(2) = MAT(2,0) ;
   v2(0) = MAT(0,1) - eigenvalues[1] ; 
   v2(1) = MAT(1,1) ;
   v2(2) = MAT(2,1) ;
   eig_vecs(0,0) = v1() 
   eig_vecs(1,0) =  
   eig_vecs(2,0) =  
}


