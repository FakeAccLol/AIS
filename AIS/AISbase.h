#pragma once

#include "AIS.h"
class AISbase :
    public AIS
{
public:
    AISbase(Options opt);
    void run();
};

