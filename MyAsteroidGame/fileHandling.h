#pragma once
#include <string>
#include <set>

void ReadFromFile(std::string str,std::set<unsigned int,std::greater<unsigned int>> &myset);
void WriteToFile(std::string str, std::set<unsigned int, std::greater<unsigned int>>& myset);