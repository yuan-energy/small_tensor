#include "../ltensor/LTensor.h"
#include "eigenvalue.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include<iomanip>
#include <string>

using namespace std;
#define MSIZE_DEFAULT 27 
#define NSIZE_DEFAULT 6
#define KSIZE_DEFAULT 6
#define BATCH_AMOUNT_DEFAULT 10000
// Index<'i'> _i;
// Index<'j'> _j;
// Index<'k'> _k;
// Index<'l'> _l;
// Index<'m'> _m;
// Index<'n'> _n;


int
main
(int argc, char* argv[])
{
	double _shear_modulus = 2.0E7 ; 
	double poisson          = 0.1 ;
	double _vol_K           = _shear_modulus / 3. / (1. - 2. * poisson) ;
	DTensor4 stiffness(3,3,3,3,0.);
	stiffness(_i,_j,_k,_l) = 
	_vol_K * kronecker_delta(_i,_j) * kronecker_delta(_k,_l) + _shear_modulus * 
	(
		kronecker_delta(_i,_k)*kronecker_delta(_j,_l) + kronecker_delta(_i,_l) * kronecker_delta(_j,_k) 
		+ (-1.) * 
		2./3. * kronecker_delta(_i,_j) * kronecker_delta(_k,_l)
	);

	
	DTensor2 strain(3,3,0.);
	DTensor2 stress(3,3,0.);
	strain(0,0) = 0.0019; 
	strain(1,1) = 0.0010;
	strain(2,2) = 0.0018; 
	strain(0,1) = 0.0011;
	strain(0,2) = 0.0012;
	strain(1,2) = 0.0016;
	strain(1,0) = strain(0,1);
	strain(2,0) = strain(0,2);
	strain(2,1) = strain(1,2);

	vector<double> eigs(3,0);
	eigs = eigenvalues(strain); 

	DTensor2 sym_strain(3,3,0.);
	DTensor2 sym_stress(3,3,0.);

	sym_strain(0,0) = eigs[0];
	sym_strain(1,1) = eigs[1];
	sym_strain(2,2) = eigs[2];

	stress(_i, _j) =   stiffness(_i, _j, _k, _l) * strain(_k, _l);
	sym_stress(_i, _j) =   stiffness(_i, _j, _k, _l) * sym_strain(_k, _l);

	cout<<"stress     = " << stress <<endl;
	eigs = eigenvalues(stress); 
	cout<<"eig of stress = " << eigs[0] << "\t" << eigs[1] << "\t" << eigs[2] << "\n";

	cout<<"sym_stress = " << sym_stress <<endl;

	cout<<"Finished! " <<endl;
	return 0; 
}