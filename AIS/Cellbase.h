#pragma once
#include "Cell.h"

class Cellbase : public Cell
{
public:
	Cellbase(size_t dim, function<double(vector<double> x)> f, vector<pair<double, double>> bounds);

	void mutate(int rate);
};

