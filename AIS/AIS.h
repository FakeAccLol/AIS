#pragma once
#include "Cell.h";
#include "Options.h"

class AIS
{
public:
	AIS(Options opt);

	virtual void run() = 0;

	int calls;
protected:
	vector<std::unique_ptr<Cell>> population;
	Options params;
};

