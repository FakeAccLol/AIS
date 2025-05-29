#pragma once

#include "AIS.h"
class AISmod :
    public AIS
{
public:
    AISmod(Options opt);
    std::unique_ptr<AIS> clone() const override {
        return std::make_unique<AISmod>(*this);
    }
    void run();
};

