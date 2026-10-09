#pragma once
#include "Model.h"

class NonLinearModel : public Model {
private:
    double a, b;
    double y_t;
public:
    NonLinearModel(double _a, double _b);
    double step(double u) override;
    void reset() override;
};
