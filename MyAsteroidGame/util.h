#pragma once
#include <random>

float rand0to1();

struct Disk {
	float cx, cy;
	float radius;
};

bool choose0or1();

void chooseMeteor(std::string& str, std::string& str2);
