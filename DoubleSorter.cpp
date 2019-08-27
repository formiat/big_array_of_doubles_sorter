#include "DoubleSorter.h"

#include <fstream>
#include <cstdio>
#include <iomanip>
#include <cmath>

MyLib::DoubleSorter::DoubleSorter(const std::string& inputTextFileName, const std::string& outputTextFileName, Order order, int maxRamUsageInBytes)
	: quantity(0)
	, order(order)
	, inputTextFileName(inputTextFileName)
	, outputTextFileName(outputTextFileName)
	, tempSrcByteFileName("tempFile1")
	, tempDestByteFileName("tempFile2")
{
	translateTextFileToByteFile();

	auto oldQuantity = quantity;
	quantity = 1 << (size_t)ceil(std::log2(quantity));

	dummyQuantity = quantity - oldQuantity;

	appendDummiesToByteFile();

	if (maxRamUsageInBytes == -1 || maxRamUsageInBytes < tenMegabytesInBytes) {
		partsCount = 1;
	} else {
		size_t maxQuantityInMemory = 1 << (size_t)floor( std::log2( (maxRamUsageInBytes - fiveMegabytesInBytes) / sizeof(double) ) );

		partsCount = quantity / (maxQuantityInMemory / (rowsCount + halfRowsCount / 2));

		if (partsCount < 1) {
			partsCount = 1;
		}
	}

	rowSize = quantity / partsCount;
	halfRowSize = rowSize / 2;
	iterationsCount = (size_t)std::log2(quantity);
}

bool MyLib::DoubleSorter::compare(double a, double b)
{
	return (order == Order::ascending) ? (a < b) : (a > b);
}

void MyLib::DoubleSorter::appendDummiesToByteFile()
{
	std::ofstream outputTempFile(tempDestByteFileName, std::fstream::binary | std::fstream::app);

	double number = 0.0;
	for (size_t i = 0; i < dummyQuantity; i++)
	{
		outputTempFile.write(reinterpret_cast<char*>(&number), sizeof number);
	}

	outputTempFile.close();
}

void MyLib::DoubleSorter::translateTextFileToByteFile()
{
	std::ifstream inputFile(inputTextFileName);
	std::ofstream outputTempFile(tempDestByteFileName, std::fstream::binary);

	double number;
	while (inputFile >> number)
	{
		outputTempFile.write(reinterpret_cast<char*>(&number), sizeof number);

		quantity++;
	}

	inputFile.close();
	outputTempFile.close();
}

void MyLib::DoubleSorter::mergeSort()
{
	std::vector<double> row(rowSize);
	std::vector<double> halfRow1(halfRowSize);
	std::vector<double> halfRow2(halfRowSize);

	for (size_t h = 0; h < iterationsCount; h++)
	{
		std::ifstream inputFile(tempSrcByteFileName, std::fstream::binary);
		std::ofstream outputFile(tempDestByteFileName, std::fstream::binary);

		for (long long i = 0; i < partsCount; i++)
		{
			inputFile.seekg(i * halfRowSize * sizeof(double));
			inputFile.read(reinterpret_cast<char*>(&halfRow1[0]), halfRowSize * sizeof(double));

			inputFile.seekg((i * halfRowSize + quantity / 2) * sizeof(double));
			inputFile.read(reinterpret_cast<char*>(&halfRow2[0]), halfRowSize * sizeof(double));

			size_t k = 0;
			for (size_t j = 0; j < halfRowSize; j++)
			{
				if (compare(halfRow1[j], halfRow2[j])) {
					row[k++] = halfRow1[j];
					row[k++] = halfRow2[j];
				} else {
					row[k++] = halfRow2[j];
					row[k++] = halfRow1[j];
				}
			}

			outputFile.write(reinterpret_cast<char*>(&row[0]), rowSize * sizeof(double));
		}

		inputFile.close();
		outputFile.close();

		std::swap(tempSrcByteFileName, tempDestByteFileName);
	}

	std::swap(tempSrcByteFileName, tempDestByteFileName);
}

void MyLib::DoubleSorter::translateByteFileToTextFile()
{
	std::ifstream inputFile(tempDestByteFileName, std::fstream::binary);
	std::ofstream outputFile(outputTextFileName);

	double number;
	inputFile.read(reinterpret_cast<char*>(&number), sizeof(double));
	while (!inputFile.eof())
	{
		if (( dummyQuantity != 0 ) && ( number == 0.0 )) {
			dummyQuantity--;
		} else {
			outputFile << std::scientific << std::setprecision(10) << number << std::endl;
		}

		inputFile.read(reinterpret_cast<char*>(&number), sizeof(double));
	}

	inputFile.close();
	outputFile.close();
}

void MyLib::DoubleSorter::sort()
{
	std::swap(tempSrcByteFileName, tempDestByteFileName);
	mergeSort();

	translateByteFileToTextFile();

	std::remove(tempSrcByteFileName.c_str());
	std::remove(tempDestByteFileName.c_str());
}
