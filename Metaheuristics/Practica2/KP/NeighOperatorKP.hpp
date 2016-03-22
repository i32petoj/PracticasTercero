#ifndef NEIGH_OPERATOR_KP_
#define NEIGH_OPERATOR_KP_

#include "SolutionKP.hpp"
#include <cstdlib>     /* srand, rand */

#include <vector>
#include <iostream>
class NeighOperatorKP{

	public:
	//:D
	NeighOperatorKP(){};

	SolutionKP getNeighSolution(const SolutionKP &sol, const int &capacity){
		std::vector <knapsack> aux = sol.getSolution();
		SolutionKP ret;
		SolGeneratorKP generator;
		int a;
		//bool flag=false;

			a = std::rand()%aux.size();
			//std::cout << a << std::endl;
			aux[a].token = !aux[a].token;
			ret.setSolution(aux);

		return ret;
	}

};

#endif