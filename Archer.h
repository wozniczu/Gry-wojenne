#pragma once
#include "Unit.h"

class Archer : public Unit {
public:
    Archer(float x, float y, bool team);
    void update(const std::vector<Unit*>& enemies) override;
};
