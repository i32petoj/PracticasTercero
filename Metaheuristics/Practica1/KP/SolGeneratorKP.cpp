#include "SolGeneratorKP.hpp"
#include <iostream>


	void SolGeneratorKP::printSol(){
		//This prints the vector
		std::vector<knapsack> aux = getSolutionKP();
		InstanceKP instancia;
		// Fuck this shit
		/*
		for(int i =0; i<aux.size(); i++){
			if(aux[i].token==true){
				std::cout << i << ", " << aux[i].price << ", " << aux[i].weight << std::endl;
			}
		}
		*/
		std::cout << std::endl << "Total price: " << instancia.getPrice(aux) << std::endl;
		std::cout << "Total Weight: " << getWeight(aux) << std::endl;

	}
	bool SolGeneratorKP::compareSol(const std::vector<knapsack> &v, const int &weigth){
		return (getWeight(v)<=weigth);
	}
	void SolGeneratorKP::generateSol(InstanceKP instancia){
		bool exit=false;
		std::vector<knapsack> aux = instancia.getSolutionKP();
		int index;

		for (int i = 0; i < 1000; ++i)
		{
			exit=false;
			aux = instancia.getSolutionKP();
			while(exit!=true){
				index = rand()%aux.size();
				if(aux[index].token==false){
					aux[index].token=true;
				}
				if (compareSol(aux, instancia.getCapacity())==false)
				{
					aux[index].token=false;
					exit=true;
				}
			}
			if(instancia.getPrice(aux)>instancia.getPrice(getSolutionKP())){
				std::cout << std::endl << "Iteration " << i;
				setSolutionKP(aux);
				printSol();
			}
		}
	}

	int SolGeneratorKP::getWeight(const std::vector<knapsack> &v){
		int result=0;
		for (unsigned int i = 0; i < v.size(); i++)
		{
			if(v[i].token==true)
				result+=v[i].weight;
		}
		return result;
	};
