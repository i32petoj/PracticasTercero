#include <iostream>
#include "InstanceMDP.hpp"
#include "grasp.hpp"
#include "BINeighExploratorMDP.hpp"
#include "FINeighExploratorMDP.hpp"
#include "NeighOperatorMDP.hpp"
#include <fstream>

int main(int argc, char ** argv){
	std::string fileName, fileNameWrite;
	std::ofstream myfile;
	int option, iterations;
	srand(time(NULL));


	if(argc!=3){
		std::cout << "Comandos mal" << std::endl;
		std::cout << "Programa iteraciones ficheroSalida" << std::endl;
		exit(-1);
	}else{
		iterations = atoi(argv[1]);
		fileNameWrite = argv[2];
	}
	
	//Ask the user which one we want to read
	std::cout << "File? " << std::endl << "\t1) 50 m5" << std::endl <<"\t2) 50 m15"
	 << std::endl << "\t3) 100 m10 \t4) 125 m12 \t5) 125 m37 \t6) 150 m15 \t7) 150 m45 \t8) 25 m7" << std::endl;
	std::cin >> option;
	switch(option){
		case 1:
			fileName = "GKD-b_13_n50_m5.txt";
			break;
		case 2:
			fileName = "GKD-b_17_n50_m15.txt";
			break;
		case 3:
			fileName = "GKD-b_24_n100_m10.txt";
			break;
		case 4:
			fileName = "GKD-b_31_n125_m12.txt";
			break;
		case 5:
			fileName = "GKD-b_39_n125_m37.txt";
			break;
		case 6:
			fileName = "GKD-b_44_n150_m15.txt";
			break;			
		case 7:
			fileName = "GKD-b_46_n150_m45.txt";
			break;
		case 8:
			fileName = "GKD-b_6_n25_m7.txt";
			break;
		default:
			fileName = "GKD-b_6_n25_m7.txt";
			break;
	}

	InstanceMDP instance(fileName);

	instance.readFile();


	Grasp graspito(instance);

	graspito.runGraspFile(fileNameWrite, iterations);

	return 1;
}