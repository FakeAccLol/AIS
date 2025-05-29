#pragma once

#include "Cell.h";
#include "Options.h"

class AIS
{
public:
	AIS(Options opt);
	virtual std::unique_ptr<AIS> clone() const = 0;
	virtual void run() = 0;

	void setOpt(Options opt);

	void set_foo(function<double(vector<double>)> foo);

	int calls;
	vector<pair<int, double>> info; // итерация и значение
protected:
	vector<std::unique_ptr<Cell>> population;
	function<double(vector<double>)> foo;
	Options params;
};

