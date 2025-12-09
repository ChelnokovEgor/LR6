#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

void printMatrix(const vector<vector<double>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        cout << "[";
        for (int j = 0; j < n; j++) {
            cout << fixed << setprecision(6) << setw(12) << matrix[i][j];
        }
        cout << " | " << fixed << setprecision(6) << setw(12) << matrix[i][n] << " ]\n";
    }
    cout << "\n";
}

void gaussElimination(vector<vector<double>>& matrix) {
    int n = matrix.size();

    for (int k = 0; k < n - 1; k++) {
        int pivotRow = k;
        double max_val = fabs(matrix[k][k]);

        for (int i = k + 1; i < n; i++) {
            double val = fabs(matrix[i][k]);
            if (val > max_val) {
                max_val = val;
                pivotRow = i;
            }
        }

        if (pivotRow != k) {
            swap(matrix[k], matrix[pivotRow]);
            cout << "Обмен строк " << (k + 1) << " и " << (pivotRow + 1) << "\n";
        }

        for (int i = k + 1; i < n; i++) {
            if (fabs(matrix[k][k]) < 1e-10) {
                cout << "Матрица вырожденная или плохо обусловленная!\n";
                return;
            }

            double factor = matrix[i][k] / matrix[k][k];
            for (int j = k; j <= n; j++) {
                matrix[i][j] -= factor * matrix[k][j];
            }
        }

        cout << "Шаг " << (k + 1) << ":\n";
        printMatrix(matrix);
    }
}

vector<double> backSubstitution(const vector<vector<double>>& matrix) {
    int n = matrix.size();
    vector<double> x(n, 0.0);

    for (int i = n - 1; i >= 0; i--) {
        if (fabs(matrix[i][i]) < 1e-10) {
            cout << "Нулевой диагональный элемент! Система может не иметь единственного решения.\n";
            return x;
        }

        double sum = matrix[i][n];
        for (int j = i + 1; j < n; j++) {
            sum -= matrix[i][j] * x[j];
        }
        x[i] = sum / matrix[i][i];
    }

    return x;
}

void gauss() {
    const int n = 4;

    vector<vector<double>> matrix = {
        { 0.89, -0.04,  0.21, -18.00, -1.24 },
        { 0.25, -1.23,  0.08,  -0.09, -1.21 },
        { -0.21,  0.08,  0.80,  -0.13,  2.56 },
        { 0.15, -1.31,  0.06,  -1.21,  0.89 }
    };

    cout << "Исходная расширенная матрица [A | b]:\n";
    printMatrix(matrix);

    gaussElimination(matrix);

    vector<double> solution = backSubstitution(matrix);

    cout << "Решение системы:\n";
    for (int i = 0; i < n; ++i) {
        cout << "x[" << (i + 1) << "] = " << fixed << setprecision(10) << solution[i] << "\n";
    }
    cout << "\n";

}



// функция проверки диагонального преобладания матрицы
bool checkDiagonalDominance(const vector<vector<double>>& matrix) {
    int size = matrix.size();
    for (int i = 0; i < size; ++i) {
        double sum = 0;
        for (int j = 0; j < size; ++j) {
            if (j != i) {
                sum += fabs(matrix[i][j]);
            }
        }
        if (fabs(matrix[i][i]) <= sum) {
            cout << "Нет диагонального преобладания в строке " << i + 1 << endl;
            return false;
        }
    }
    return true;
}

// метод Зейделя для решения системы
void solveSeidel() {
    double epsilon = 1e-3;
    int maxIterations = 5;

    vector<vector<double>> matrixA = {
        { 0.89, -0.04,  0.21, -18.00, -1.24 },
        { 0.25, -1.23,  0.08,  -0.09, -1.21 },
        { -0.21,  0.08,  0.80,  -0.13,  2.56 },
        { 0.15, -1.31,  0.06,  -1.21,  0.89}
    };
    vector<double> vectorB = { -1.24, -1.21, 2.56, 0.89 };

    // проверяем диагональное преобладание матрицы
    if (!checkDiagonalDominance(matrixA)) {
        cout << "Метод Зейделя может не сойтись из-за отсутствия диагонального преобладания\n";
    }

    // решение методом Зейделя
    int size = matrixA.size();
    vector<double> solution(size, 0);
    int iterations = 0;
    double error;

    do {
        error = 0;
        vector<double> oldSolution = solution;

        for (int i = 0; i < size; ++i) {
            double sum = 0;
            for (int j = 0; j < size; ++j) {
                if (j != i) sum += matrixA[i][j] * solution[j];
            }
            double newValue = (vectorB[i] - sum) / matrixA[i][i];
            error = max(error, fabs(newValue - solution[i]));
            solution[i] = newValue;
        }

        iterations++;
    } while (error > epsilon && iterations < maxIterations);

    // вывод результатов
    cout << "Решение системы методом Зейделя:\n";
    cout << "Количество итераций: " << iterations << endl;
    cout << "x1 = " << fixed << setprecision(6) << solution[0] << endl;
    cout << "x2 = " << fixed << setprecision(6) << solution[1] << endl;
    cout << "x3 = " << fixed << setprecision(6) << solution[2] << endl;
    cout << "x4 = " << fixed << setprecision(6) << solution[3] << endl;

}
