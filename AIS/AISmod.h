#pragma once

#include "AIS.h"
class AISmod :
    public AIS
{
public:
    AISmod(Options opt);
    void run();
};

