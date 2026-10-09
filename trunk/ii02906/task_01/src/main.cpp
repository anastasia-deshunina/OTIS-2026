#include <iostream>
#include <fstream>   
#include <cmath>
#include "LinearModel.h"
#include "NonLinearModel.h"
#include "DiffEqModel.h"

double getInput(int tau, int type) {
    if (type == 1) return 1.0;
    if (type == 2) return (tau == 0) ? 1.0 : 0.0;
    if (type == 3) return std::sin(tau);
    return 0.0;
}

int main() {
    LinearModel linModel(0.5, 0.2, 0.1, 1.0);
    // Проверка устойчивости
    if (linModel.isStable()) {
        std::cout << "System is STABLE.\n";
    }
    else {
        std::cout << "WARNING: System is UNSTABLE!\n";
    }
    NonLinearModel nonlinModel(0.5, 0.5);
    DiffEqModel diffModel(0.1, 0.01);

    // Открываем файл для записи
    std::ofstream outFile("results.csv");

    // Записываем заголовок в файл
    outFile << "Step,Input u,Linear y,Nonlinear y,DiffEq y\n";

    std::cout << "Step\tInput u\tLinear y\tNonlinear y\tDiffEq y\n";
    int n = 10;
    for (int tau = 0; tau < n; ++tau) {
        // Выбор типа входного воздействия: 1 - ступенчатое, 2 - импульсное, 3 - гармоническое
        int inputType = 1; // Можно поменять на 2 или 3
        double u = getInput(tau, inputType);

        double y_lin = linModel.step(u);
        double y_non = nonlinModel.step(u);
        double y_diff = diffModel.step(u);

        // Вывод в консоль
        std::cout << tau << "\t" << u << "\t\t" << y_lin << "\t\t" << y_non << "\t\t" << y_diff << "\n";

        // Вывод в файл CSV
        outFile << tau << "," << u << "," << y_lin << "," << y_non << "," << y_diff << "\n";
    }

    outFile.close();
    std::cout << "\nData saved to results.csv\n";

    return 0;
}