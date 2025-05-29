#pragma once
#include "AISbase.h"
#include "AISmod.h"

namespace testing
{
	void testShrinkRate(std::unique_ptr<AIS> method);
	void testPopulationSize(std::unique_ptr<AIS> method);
	void testDimSize(std::unique_ptr<AIS> method);
	void testMutationRate(std::unique_ptr<AIS> method);
	void testGenAmount(std::unique_ptr<AIS> method);
};

