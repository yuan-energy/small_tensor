// #include "../../../smalltensor::ad/app/smalltensor.h"
#include "../ltensor/LTensor.h"
#include "dp.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
// using namespace std;
// using namespace LTensor;
int main(int argc, char const *argv[])
{
	Index<'i'> _i;
	Index<'j'> _j;
	Index<'k'> _k;
	Index<'l'> _l;

	double _shear_modulus   = 2E7 ;
	double poisson          = 0.1;
	double _vol_K           = _shear_modulus / 3. / (1. - 2. * poisson) ;
	double _eta             = 0.2  ;
	double _eta_bar         = 0.2  ;
	double _cohesion        = 100  ;
	double _initial_confine = 330000 ;
	DVEC material_constants{_shear_modulus, 
							_vol_K, 
							_eta, 
							_eta_bar, 
							_cohesion
							}; 
	auto theMaterial = new dp(material_constants, _initial_confine) ; 

	DTensor2 input_strain(3,3,0.) ;
	input_strain *= 0. ;
	double max_strain = 0.1;
	int Nstep = 100;
	input_strain(0,1) = max_strain / Nstep ;
	input_strain(1,0) = input_strain(0,1);
	ofstream fout("strain_stress.txt");
	DTensor2 stress_ret(3,3,0.) ;
	DTensor2 strain_ret(3,3,0.) ;

	// **************************************************************
	// Write the initial state
	// **************************************************************
	stress_ret = theMaterial->getCommitStress();
	strain_ret = theMaterial->getCommitStrain();
	std::cout<< strain_ret(0,1) <<"\t" << stress_ret(0,1) <<std::endl;
	fout<< strain_ret(0,1) <<"\t" << stress_ret(0,1) <<std::endl;
	// **************************************************************
	// Loading
	// **************************************************************
	input_strain(0,2) =  input_strain(0,1) /27.;
	input_strain(1,2) =  input_strain(0,1) /40.;
	input_strain(0,0) =  input_strain(0,1) /12.;
	input_strain(1,1) = (-1.)* input_strain(0,1) /30.;
	input_strain(2,2) = (-1.)* input_strain(0,1) /50.;
	// =========
	input_strain(2,0) =  input_strain(0,2);
	input_strain(2,1) =  input_strain(1,2);
	// =========
	auto prev_stress = theMaterial->getCommitStress();
	auto stress_integrate = prev_stress ; 
	auto stress_multiply = prev_stress ; 
	auto diff = prev_stress ; 
	for (int step = 0; step < 3; ++step)
	{
		prev_stress = theMaterial->getCommitStress();
		auto stiffness = theMaterial->getTangentTensor();
		theMaterial->setStrainIncr(input_strain); 
		theMaterial->CommitState();
		stress_ret = theMaterial->getCommitStress();
		strain_ret = theMaterial->getCommitStrain();
		std::cout<< strain_ret(0,1) <<"\t" << stress_ret(0,1) <<std::endl;
		fout<< strain_ret(0,1) <<"\t" << stress_ret(0,1) <<std::endl;

		stress_integrate(_i,_j) = stress_ret(_i,_j) - prev_stress(_i,_j);
		stress_multiply(_i,_j) = stiffness(_i,_j,_k,_l) * input_strain(_k,_l) ; 
		diff(_i,_j) = stress_multiply(_i,_j) - stress_integrate(_i,_j) ; 
		std::cout<<"*******************************************************\n";
		std::cout<<"Step Number = " << step <<std::endl;
		std::cout<<"diff stress = " << diff <<std::endl;
		std::cout<<"-------------------------------------------------------\n";
		std::cout<<"stress_multiply = " << stress_multiply <<std::endl;
		std::cout<<"stress_integrate= " << stress_integrate <<std::endl;
		// std::cout<<"stress_ret      = " << stress_ret       <<std::endl;
		// std::cout<<"prev_stress     = " << prev_stress       <<std::endl;
		std::cout<<"*******************************************************\n";
	}


	int Nloop = 0 ; 
	for (int loop = 0; loop < Nloop; ++loop)
	{
		// **************************************************************
		// Un-Loading
		// **************************************************************
		std::cout<<" Un-Loading! ~~~~~~~~~~~~~~~~~~~" <<std::endl;
		input_strain(_i,_j) = -1. * input_strain(_i,_j);
		for (int step = 0; step < 1 * Nstep + 1 ; ++step)
		{
			prev_stress = theMaterial->getCommitStress();
			auto stiffness = theMaterial->getTangentTensor();

			theMaterial->setStrainIncr(input_strain); 
			theMaterial->CommitState();
			stress_ret = theMaterial->getCommitStress();
			strain_ret = theMaterial->getCommitStrain();
			std::cout<< strain_ret(0,1) <<"\t" << stress_ret(0,1) <<std::endl;
			fout<< strain_ret(0,1) <<"\t" << stress_ret(0,1) <<std::endl;

			stress_integrate(_i,_j) = stress_ret(_i,_j) - prev_stress(_i,_j);
			stress_multiply(_i,_j) = stiffness(_i,_j,_k,_l) * input_strain(_k,_l) ; 
			diff(_i,_j) = stress_multiply(_i,_j) - stress_integrate(_i,_j) ; 
			std::cout<<"*******************************************************\n";
			std::cout<<"Step Number = " << step <<std::endl;
			std::cout<<"diff stress = " << diff <<std::endl;
			std::cout<<"-------------------------------------------------------\n";
			std::cout<<"stress_multiply = " << stress_multiply <<std::endl;
			std::cout<<"stress_integrate= " << stress_integrate <<std::endl;
			std::cout<<"*******************************************************\n";
		}

		// // **************************************************************
		// // Re-Loading
		// // **************************************************************
		// std::cout<<" Re-Loading! ~~~~~~~~~~~~~~~~~~~" <<std::endl;
		// input_strain(_i,_j) = -1. * input_strain(_i,_j);
		// for (int step = 0; step < 2 * Nstep; ++step)
		// {
		// 	prev_stress = theMaterial->getCommitStress();

		// 	theMaterial->setStrainIncr(input_strain); 
		// 	theMaterial->CommitState();
		// 	stress_ret = theMaterial->getCommitStress();
		// 	strain_ret = theMaterial->getCommitStrain();
		// 	std::cout<< strain_ret(0,1) <<"\t" << stress_ret(0,1) <<std::endl;
		// 	fout<< strain_ret(0,1) <<"\t" << stress_ret(0,1) <<std::endl;
			
		// 	stress_integrate(_i,_j) = stress_ret(_i,_j) - prev_stress(_i,_j);
		// 	auto stiffness = theMaterial->getTangentTensor();
		// 	stress_multiply(_i,_j) = stiffness(_i,_j,_k,_l) * input_strain(_k,_l) ; 
		// 	diff(_i,_j) = stress_multiply(_i,_j) - stress_integrate(_i,_j) ; 
		// 	std::cout<<"Step Number = " << step <<std::endl;
		// 	std::cout<<"diff stress = " << diff <<std::endl;

		// }
	}


	delete theMaterial;
	return 0;
}