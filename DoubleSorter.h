#pragma once

#include <string>
#include <vector>

namespace MyLib {
	class DoubleSorter
	{
	public:
		enum class Order {
			ascending,
			descending
		};

	private:
		static const size_t fiveMegabytesInBytes = 1024 * 1024 * 5;
		static const size_t tenMegabytesInBytes = 2 * fiveMegabytesInBytes;
		static const size_t rowsCount = 1;
		static const size_t halfRowsCount = 2;

	private:
		size_t quantity;
		size_t partsCount;
		size_t rowSize;
		size_t halfRowSize;
		size_t iterationsCount;
		size_t dummyQuantity;
		Order order;
		std::string inputTextFileName;
		std::string outputTextFileName;
		std::string tempSrcByteFileName;
		std::string tempDestByteFileName;

	public:
		// maxRamUsageInBytes == -1 means that algorithm can use as much memory as needed
		DoubleSorter(const std::string& inputTextFileName, const std::string& outputTextFileName, Order order = Order::ascending, int maxRamUsageInBytes = -1);

	private:
		bool compare(double a, double b);
		void appendDummiesToByteFile();
		void translateTextFileToByteFile();
		void mergeSort();
		void translateByteFileToTextFile();

	public:
		void sort();
	};
}

