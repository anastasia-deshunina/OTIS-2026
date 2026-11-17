#define LAB2_MARKER_02906

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <string>
#include "LinearModel.h"
#include "NonLinearModel.h"
#include "DiffEqModel.h"

using namespace std;

int getUserChoice()
{
    int choice;
    cout << "Выберите модель:" << endl;
    cout << "1 - Линейная " << endl;
    cout << "2 - Нелинейная" << endl;
    cout << "3 - Дифференциальное" << endl;
    cout << "Ваш выбор: ";
    cin >> choice;
    return choice;
}

int getSignalChoice() 
{
    int choice;
    cout << "\nВыберите тип входного воздействия:" << endl;
    cout << "1 - Ступенчатое " << endl;
    cout << "2 - Импульсное " << endl;
    cout << "3 - Гармоническое " << endl;
    cout << "Ваш выбор: ";
    cin >> choice;
    return choice;
}

double getInput(int tau, int type)
{
    if (type == 1) return 1.0;
    if (type == 2) return (tau == 0) ? 1.0 : 0.0;
    if (type == 3) return std::sin(tau);
    return 0.0;
}

int main()
{
    setlocale(0, "");
    int modelChoice = getUserChoice();
    int signalChoice = getSignalChoice();

    // Ввод коэффициентов для линейной модели
    double a1, a2, a3, b;
    cout << "\nВведите коэффициенты для линейной модели (a1, a2, a3, b): ";
    cin >> a1 >> a2 >> a3 >> b;

    int n;
    cout << "Введите количество шагов: ";
    cin >> n;

    // Создаем модели с введенными коэффициентами
    LinearModel linModel(a1, a2, a3, b);
    NonLinearModel nonlinModel(0.5, 0.5);
    DiffEqModel diffModel(0.1, 0.01);

    // ПРОВЕРКА УСТОЙЧИВОСТИ ДО НАЧАЛА СИМУЛЯЦИИ (Пункт 2 задания)
    if (modelChoice == 1) 
    
    {
        cout << "\n--- Анализ устойчивости ---" << endl;
        if (linModel.isStable()) {
            cout << "System is STABLE." << endl;
        }
        else {
            cout << "WARNING: System is UNSTABLE! Simulation may diverge." << endl;
        }
        cout << "---------------------------\n" << endl;
    }

    ofstream outFile("results.csv");
    outFile << "Step;Input u;Output y\n";

    cout << setw(6) << "Step" << setw(12) << "Input u" << setw(15) << "Output y" << endl;

    for (int tau = 0; tau < n; ++tau)
    {
        double u = getInput(tau, signalChoice);
        double y = 0.0;

        if (modelChoice == 1) {
            y = linModel.step(u);
        }
        else if (modelChoice == 2) {
            y = nonlinModel.step(u);
        }
        else if (modelChoice == 3) {
            y = diffModel.step(u);
        }

        cout << fixed << setprecision(6);
        cout << setw(6) << tau << setw(12) << u << setw(15) << y << endl;

        outFile << tau << ";" << u << ";" << y << "\n";
    }
    outFile.close();

    cout << "\nДанные сохранены. Генерация графика" << endl;

    // Запуск Python для построения графика
    string plotCmd = "python trunk/ii02906/task_01/plot_results.py results.csv result_plot.png";
    int result = system(plotCmd.c_str());

    if (result == 0) {
        system("start result_plot.png");
    }
    else {
        cout << "[WARNING] Произошла ошибка при построении графика!!!" << endl;
    }

    return 0;
}