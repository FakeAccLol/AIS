#include "Cellbase.h"

Cellbase::Cellbase(size_t dim, function<double(vector<double> x)> f, vector<pair<double, double>> bounds) : Cell(dim, f, bounds) {

}

void Cellbase::mutate(int rate)
{

}
