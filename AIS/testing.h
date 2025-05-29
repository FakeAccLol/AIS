#pragma once
#include "AISbase.h"
#include "AISmod.h"

namespace testing
{
	struct Return {
		vector<double> timeStamps;
		vector<size_t> calls;
		vector<vector<pair<int, double>>> info;
	};

	Return testShrinkRate(std::unique_ptr<AIS> method);
	Return testPopulationSize(std::unique_ptr<AIS> method);
	Return testDimSize(std::unique_ptr<AIS> method);
	Return testMutationRate(std::unique_ptr<AIS> method);
	Return testGenAmount(std::unique_ptr<AIS> method);
};

