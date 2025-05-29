#pragma once
#include "Cell.h"

class Cellmod : public Cell
{
public:
	Cellmod(size_t dim, function<double(vector<double> x)> f, vector<pair<double, double>> bounds);
	virtual std::unique_ptr<Cellmod> clone() const;

	void mutate(int rate);
};


