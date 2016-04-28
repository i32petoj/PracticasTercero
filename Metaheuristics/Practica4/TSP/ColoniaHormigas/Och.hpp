#ifndef OCH_HPP
#define OCH_HPP

#include <vector>
#include <limits>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include "InstanceTSP.hpp"
#include "SolutionTSP.hpp"
#include "SolGeneratorTSP.hpp"

//CAMBIOS

struct Ant{
	std::vector <node> solution;
	double aportePheromonas;
	double distancia;
};


class Och{

	private:
		double pheromone_;
		double alpha_;
		double beta_;
		int numAnt_;
		SolutionTSP bestSolution_;
		double vaporizePercentage_;
		std::vector< std::vector <double> > pheromoneMatrix_;
		std::vector< std::vector <double> > distanceMatrix_;
		std::vector< std::vector <double> > heuristicMatrix_;
		std::vector<node> original_;
		std::vector<Ant> hormiguitas_;

	public:


		Och(const InstanceTSP &instance){
			setPheromone(10);
			setVaporizePercentage(0.1);
			setBeta(2);
			setAlpha(1);
			setNumAnt(5);
			//CAMBIOS
			setBestSolution(instance.getSolutionTSP());
			setOriginal(instance.getSolutionTSP());
			fillMatrix(instance.getSolutionTSP().size());
			fillDistanceAndHeuristicMatrix(instance.getSolutionTSP());
		}

		void setPheromone(const double &pherom){
			pheromone_ = pherom;
		}

		double getPheromone() const{
			return pheromone_;
		}

		void setAlpha(const double &alpha){
			alpha_ = alpha;
		}

		double getAlpha() const{
			return alpha_;
		}

		void setBeta(const double &beta){
			beta_ = beta;
		}

		double getBeta() const{
			return beta_;
		}

		int getNumAnt() const{
			return numAnt_;
		}

		void setNumAnt(const int &numAnt){
			numAnt_ = numAnt;
		}

		void setVaporizePercentage(const double &perc){
			vaporizePercentage_ = perc;
		}

		double getVaporizePercentage() const{
			return vaporizePercentage_;
		}

		void setHormiguitas(const std::vector<Ant> &hormi){
			hormiguitas_ = hormi;
		};

		std::vector<Ant> getHormiguitas() const{
			return hormiguitas_;
		}

		std::vector<node> getOriginal() const{
			return original_;
		}

		void setOriginal(const std::vector<node> &orig){
			original_ = orig;
		}

		SolutionTSP getBestSolution() const{
			return bestSolution_;
		}

		void setBestSolution(const std::vector<node> &solution){
			bestSolution_.setSolution(solution);
		}

		//Funciones para la construncción y uso de las hormigüitas

		void fillMatrix(const int &length);

		double aporteArco(const int &x, const int &y);

		void fillDistanceAndHeuristicMatrix(const std::vector<node> &nodes);

		double getProbability();

		void runAnts();

		void refreshPheromoneMatrix();

		node getNextNode(const int &x, const std::vector<node> &caminoHormiga);

		void getBestAntSolution();

		bool isInVector(const int &x, const std::vector<node> &caminoHormiga);

		~Och(){
			pheromoneMatrix_.clear();
		}


};

#endif