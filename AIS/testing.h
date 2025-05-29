#pragma once
#include "AISbase.h"
#include "AISmod.h"

namespace testing
{
	vector<double> testShrinkRate(std::unique_ptr<AIS> method);
	vector<double> testPopulationSize(std::unique_ptr<AIS> method);
	vector<double> testDimSize(std::unique_ptr<AIS> method);
	vector<double> testMutationRate(std::unique_ptr<AIS> method);
	vector<double> testGenAmount(std::unique_ptr<AIS> method);
};

