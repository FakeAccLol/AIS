#pragma once

#include "AIS.h"
class AISbase :
    public AIS
{
public:
    AISbase(Options opt);
    std::unique_ptr<AIS> clone() const override {
        return std::make_unique<AISbase>(*this);
    }
    void run();
};

