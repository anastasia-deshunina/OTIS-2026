#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include "LinearModel.h"
#include "NonLinearModel.h"
#include "DiffEqModel.h"

using namespace std;

int getUserChoice() {
    int choice;
    cout << "Выберите модель:" << endl;
    cout << "1 - Линейная (1.6)" << endl;
    cout << "2 - Нелинейная (2.10)" << endl;
    cout << "3 - Дифференциальное уравнение (3.4)" << endl;
    cout << "Ваш выбор (1-3): ";
    cin >> choice;
    return choice;
}

int getSignalChoice() {
    int choice;
    cout << "\nВыберите тип входного воздействия:" << endl;
    cout << "1 - Ступенчатое " << endl;
    cout << "2 - Импульсное " << endl;
    cout << "3 - Гармоническое " << endl;
    cout << "Ваш выбор (1-3): ";
    cin >> choice;
    return choice;
}

double getInput(int tau, int type) {
    if (type == 1) return 1.0;
    if (type == 2) return (tau == 0) ? 1.0 : 0.0;
    if (type == 3) return std::sin(tau);
    return 0.0;
}

int main() {
    setlocale(0, "");
    int modelChoice = getUserChoice();
    int signalChoice = getSignalChoice();

    int n;
    cout << "\nВведите количество шагов симуляции: ";
    cin >> n;

    LinearModel linModel(0.5, 0.2, 0.1, 1.0);
    NonLinearModel nonlinModel(0.5, 0.5);
    DiffEqModel diffModel(0.1, 0.01);

    ofstream outFile("results.csv");
    outFile << "Step;Input u;Output y\n";

    cout << "\n" << setw(6) << "Step" << setw(12) << "Input u" << setw(15) << "Output y" << endl;

    for (int tau = 0; tau < n; ++tau) {
        double u = getInput(tau, signalChoice);
        double y = 0.0;

        if (modelChoice == 1) {
            if (tau == 0 && !linModel.isStable()) {
                cout << "WARNING: System is UNSTABLE!" << endl;
            }
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

    cout << "\nДанные сохранены в файл results.csv" << endl;
    const char* cmd = R"(powershell -Command "$excel = New-Object -ComObject Excel.Application; $excel.Visible = $true; $workbook = $excel.Workbooks.Open('D:\OTIS\OTIS-2026\results.csv'); $worksheet = $workbook.Worksheets.Item(1); $chart = $worksheet.Shapes.AddChart2(240, 4).Chart; $chart.SetSourceData($worksheet.Range('A1:B11')); $chart.HasTitle = $true; $chart.ChartTitle.Text = 'График модели';")";
    system(cmd);
    return 0;
}