#pragma once
#include "Cell.h";
#include "Options.h"

class AIS
{
public:
	AIS(Options opt);

	virtual void run() = 0;

	void operator()(Options opt);

	void set_foo(function<double(vector<double>)> foo);

	int calls;
protected:
	vector<std::unique_ptr<Cell>> population;
	function<double(vector<double>)> foo;
	Options params;
};

