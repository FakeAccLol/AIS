#pragma once
#include "AISbase.h"
#include "AISmod.h"

namespace testing
{
	struct Return {
		// сколько времени занимала оптимизация
		vector<double> timeStamps;
		// сколько раз вызывалась целевая функция
		vector<size_t> calls;
		// для каждой оптимизации то как изменялась целевая функция 
		vector<vector<pair<int, double>>> info;
	};

	Return testShrinkRate(std::unique_ptr<AIS> method);
	Return testPopulationSize(std::unique_ptr<AIS> method);
	Return testDimSize(std::unique_ptr<AIS> method);
	Return testMutationRate(std::unique_ptr<AIS> method);
	Return testGenAmount(std::unique_ptr<AIS> method);
};

