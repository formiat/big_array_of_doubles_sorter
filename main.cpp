#include <iostream>
#include <string>

#include "DoubleGenerator.h"
#include "DoubleSorter.h"

int main(int argc, char** argv)
{
    if (argc == 4 && std::string(argv[1]) == std::string("-g")) { // Generate
        MyLib::DoubleGenerator::generateToFile(argv[2], std::stoi(argv[3]));

        return 0;
    } else if (argc == 3) { // Sort
        MyLib::DoubleSorter doubleSorter(argv[1], argv[2]);
        doubleSorter.sort();

        return 0;
    } else if (argc == 4 && (std::string(argv[3]) == std::string("-a") || std::string(argv[3]) == std::string("-d"))) { // Sort
        MyLib::DoubleSorter::Order order;

        if (std::string(argv[3]) == std::string("-a")) {
            order = MyLib::DoubleSorter::Order::ascending;
        } else {
            order = MyLib::DoubleSorter::Order::descending;
        }

        MyLib::DoubleSorter doubleSorter(argv[1], argv[2], order);
        doubleSorter.sort();

        return 0;
    } else if (argc == 5 && (std::string(argv[3]) == std::string("-a") || std::string(argv[3]) == std::string("-d"))) { // Sort
        MyLib::DoubleSorter::Order order;

        if (std::string(argv[3]) == std::string("-a")) {
            order = MyLib::DoubleSorter::Order::ascending;
        } else {
            order = MyLib::DoubleSorter::Order::descending;
        }

        MyLib::DoubleSorter doubleSorter(argv[1], argv[2], order, std::stoi(argv[4]));
        doubleSorter.sort();

        return 0;
    } else {
        std::cout << "Wrong parameters!" << std::endl;
        std::cout << "Parameters should be:" << std::endl;

        std::cout << "For generate:" << std::endl;
        std::cout << "1) <action> = \'-g\'" << std::endl;
        std::cout << "2) <output file name>" << std::endl;
        std::cout << "3) <quantity>" << std::endl;

        std::cout << "For sort:" << std::endl;
        std::cout << "1) <input file name>" << std::endl;
        std::cout << "2) <output file name>" << std::endl;
        std::cout << "3) [<order>] = \'-a\' | \'-d\'" << std::endl;
        std::cout << "4) [<max ram usage in bytes>] >= 10485760" << std::endl;

        return 1;
    }
}
