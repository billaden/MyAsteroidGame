#include "fileHandling.h"
#include <fstream>
#include <iostream>



void ReadFromFile(std::string str,std::set<unsigned int,std::greater<unsigned int>> &myset)
{
	
	std::string filename = str;
	std::string line;
	std::ifstream infile(filename);
	if(infile.is_open()){
		while (std::getline(infile, line)) {
		//	std::cout<< stoi(line) << std::endl;
			myset.insert(stoi(line));
		}
		infile.close();
	}
}

void WriteToFile(std::string str, std::set<unsigned int, std::greater<unsigned int>>& myset)
{
	std::set<unsigned int, std::greater<unsigned int>> ::iterator it;
	std::ofstream ofile;
	ofile.open(str);
	if (ofile.is_open()) {
		for (it = myset.begin(); it != myset.end(); ++it) {
			ofile << *it << std::endl;
		}
		ofile.close();
	}


}
