#pragma once
#include "Model.h"

class DiffEqModel : public Model {
private:
    double a, dt;
    double y_t;
public:
    DiffEqModel(double _a, double _dt);
    double step(double u) override;
    void reset() override;
};
