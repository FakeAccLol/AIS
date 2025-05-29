#include "AIS.h"

AIS::AIS(Options opt) : params(opt), calls(0)
{
}

void AIS::setOpt(Options opt)
{
	params = opt;
}

void AIS::set_foo(function<double(vector<double>)> foo)
{
	this->foo = foo;
}
