#pragma once
#include "util.h"
#include <time.h>

float rand0to1() {
	return rand() / (float)RAND_MAX;
}

bool choose0or1()
{
	if (rand0to1() > 0.5f) return true;
	else return false;
}

void chooseMeteor(std::string &str , std::string &str2)
{
	float ran = rand0to1();
	if (ran < 0.2f) {
		str = "meteor.png";
		str2 = "meteor-shadow.png";
	}
	else if (ran >= 0.2f && ran < 0.4f) {
		str = "meteor2.png";
		str2 = "meteor2-shadow.png";
	}
	else if (ran >= 0.4f && ran < 0.6f) {
		str = "meteor3.png";
		str2 = "meteor3-shadow.png";
	}
	else if (ran >= 0.6f && ran < 0.8f) {
		str = "meteor4.png";
		str2 = "meteor4-shadow.png";
	}
	else {
		str = "meteor5.png";
		str2 = "meteor5-shadow.png";
	}

}



