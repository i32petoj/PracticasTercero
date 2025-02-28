#include "InstanceKP.hpp"
#include "SolutionKP.hpp"
#include "SolGeneratorKP.hpp"
#include <iostream>
#include <ctime>
#include <fstream>
#include "FINeighExploratorKP.hpp"
#include "BINeighExploratorKP.hpp"
#include "LocalSearchKP.hpp"
#include "ClaseTiempo.hpp"
int main(int argc, char ** argv){
	std::string fileName;
	int option;
	SolutionKP sol, solFI, solBI;
	srand(time(NULL));
	int iterations;
	std::string fileNameWrite;
	std::ofstream myfile;
	Clock reloj;
	Clock reloj2;
	double tiempoFI=0, tiempoBI=0;
	double tiempo;

	//We check if the parameters are k :D
	if(argc!=3){
		//The parameters are wrong
		std::cout << "La forma de llamar al programa es:" << std::endl;
		std::cout << "'NombrePrograma' 'NombreFichero' 'NumeroIteraciones'" << std::endl;
		//We exit the program
		exit(-1);
	}else{
		fileNameWrite = argv[1];
		iterations = atoi(argv[2]);
		myfile.open(fileNameWrite.c_str());
		if(!myfile.is_open()){
			std::cout << "Error con el fichero" << std::endl;
			exit(-1);
		}
	}

	//Ask the user which one we want to read
	std::cout << "File? " << std::endl << "\t1) 200 elements" << std::endl <<"\t2) 500 elements"
	 << std::endl << "\t3) 10000 elements" << std::endl;
	std::cin >> option;
	switch(option){
		case 1:
			fileName = "knapPI_1_200_10000.csv";
			break;
		case 2:
			fileName = "knapPI_12_500_1000.csv";
			break;
		case 3:
			fileName = "knapPI_1_10000_1000000.csv";
			break;
		default:
			fileName = "knapPI_1_10000_1000000.csv";
			break;
	}

	InstanceKP instance(fileName);

	instance.readFile();


	//We generate the solutions and pass it to a file
	SolGeneratorKP generator(instance);

	std::cout << "\x1b[32mPasando a fichero...\x1b[0m" << std::endl;

	std::cout << "Las soluciones por diversificación:" << std::endl;
	reloj2.start();

	generator.generateSol(instance);
	sol = generator.getSolutionKP();
	FINeighExploratorKP first(sol, instance.getCapacity());
	BINeighExploratorKP best(sol, instance.getCapacity());
	solBI = sol;
	solFI = sol;

	for(int i=0; i<iterations; i++){

		
		
		FINeighExploratorKP first(solFI, instance.getCapacity());
		BINeighExploratorKP best(solBI, instance.getCapacity());

		//We are gonna write the file with this format

		//The file has changed
		//'Iteration' 'priceBase' 'WeightBase' 'priceFI' 'WeightFI''time' 'priceBI' 'WeightBI' 'time' 'PriceLocal' 'time' 'WeightLocal'
		myfile << i << " " << sol.getPrice() << " " << sol.getWeight() << " ";

		//We are also counting the time
		reloj.start();
		solFI = first.getFirstImprovement();
		reloj.stop();
		tiempo = reloj.elapsed();
		tiempoFI = tiempoFI + tiempo;
		myfile << solFI.getPrice() << " " << solFI.getWeight() << " " << tiempo << " " << tiempoFI << " ";

		reloj.start();
		solBI = best.getBestImprovement();
		reloj.stop();
		tiempo = reloj.elapsed();
		tiempoBI = tiempoBI + tiempo;
		myfile << solBI.getPrice() << " " << solBI.getWeight() << " " << tiempo << " " << tiempoBI << " ";

		//Optimal search
		/*
		reloj.start();
		sol = local.getOptimal();
		reloj.stop();
		tiempo = reloj.elapsed();
		myfile << sol.getPrice() << " " << sol.getWeight() << " " << tiempo << std::endl;
		*/
		myfile << std::endl;
	}

	reloj2.stop();

	std::cout << reloj2.elapsed()/1000000 << " segundos ha tardado esto" << std::endl;

/*
	std::cout<<std::endl<<"*Primera mejora*"<<std::endl;
	sol = first.getFirstImprovement();
	sol.printSol();

	std::cout<<std::endl<<"*Mejor mejora*"<<std::endl;
	sol = best.getBestImprovement();
	sol.printSol();

	std::cout<<std::endl<<"*Búsqueda local*"<<std::endl;
	sol = local.getOptimal();
	sol.printSol();
*/

	//We close the file
	myfile.close();
	return 1;
}