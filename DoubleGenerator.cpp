#include "DoubleGenerator.h"

#include <fstream>
#include <random>
#include <iomanip>

void MyLib::DoubleGenerator::generateToFile(std::string fileName, size_t quantity)
{
	std::ofstream outputFile(fileName);

	//std::random_device rd;
	//std::mt19937 mt(rd());
	//std::default_random_engine eng((long unsigned int)time(0));
	//std::uniform_real_distribution<double> dist(
	//	std::numeric_limits<double>::min(),
	//	std::numeric_limits<double>::max()
	//);

	int number = quantity;

	for (int i = 0; i < quantity; i++) {
		//outputFile << std::scientific << dist(mt) << std::endl;
		outputFile << std::scientific << std::setprecision(10) << (double)number << std::endl;
		number--;
		//outputFile << std::scientific << dist(eng) << std::endl;
	}
}
