#pragma once
#include "Model.h"

class LinearModel : public Model {
private:
    double a1, a2, a3, b;
    double y_t, y_t1, y_t2;
public:
    LinearModel(double _a1, double _a2, double _a3, double _b);
    double step(double u) override;
    void reset() override;
    bool isStable();
};
