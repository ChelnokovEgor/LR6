#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include <algorithm>

using namespace std;

void number11() {
    srand(time(0));

    int N;
    cout << "Задача 1: \nВведите N: ";
    cin >> N;

    vector<vector<int>> matrix(N, vector<int>(N));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 201 - 100;
        }
    }

    int maxPosCount = -1;
    int bestRowIdx = -1;

    for (int i = 0; i < N; ++i) {
        int posCount = 0;
        for (int j = 0; j < N; ++j) {
            if (matrix[i][j] > 0) ++posCount;
        }
        if (posCount > maxPosCount) {
            maxPosCount = posCount;
            bestRowIdx = i;
        }
    }

    vector<int> resultRow;
    if (bestRowIdx != -1) {
        resultRow = matrix[bestRowIdx];
    }

    cout << "\nМатрица:\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout.width(4);
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nСтрока с наибольшим количеством положительных чисел ("
        << maxPosCount << "): ";
    for (int x : resultRow) {
        cout << x << " ";
    }
    cout << endl;
    cout << endl;
}


void number12() {
    srand(static_cast<unsigned>(time(0)));

    int M, N;
    cout << "Задача 2\nВведите M и N: ";
    cin >> M >> N;

    vector<vector<int>> matrix(M, vector<int>(N));
    map<int, int> freq;

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = 100 + rand() % 51;
            freq[matrix[i][j]]++;
        }
    }

    int maxFreq = 0;
    int mostFreqNum = -1;
    for (const auto& p : freq) {
        if (p.second > maxFreq) {
            maxFreq = p.second;
            mostFreqNum = p.first;
        }
    }

    bool allUnique = true;
    for (const auto& p : freq) {
        if (p.second > 1) {
            allUnique = false;
            break;
        }
    }

    cout << "\nМатрица:\n";
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }

    if (allUnique) {
        cout << "\nВсе числа уникальны.\n\n";
    }
    else {
        cout << "\nНаиболее встречающееся число: " << mostFreqNum
            << " (встречается " << maxFreq << " раз)\n\n";
    }
}


void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int countNeighbors(const vector<vector<int>>& grid, int i, int j, int rows, int cols) {
    int count = 0;
    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            if (di == 0 && dj == 0) continue;
            int ni = (i + di + rows) % rows;
            int nj = (j + dj + cols) % cols;
            count += grid[ni][nj];
        }
    }
    return count;
}

vector<vector<int>> nextGen(const vector<vector<int>>& grid, int mode) {
    int rows = grid.size(), cols = grid[0].size();
    vector<vector<int>> next(rows, vector<int>(cols, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int alive = grid[i][j];
            int n = countNeighbors(grid, i, j, rows, cols);

            if (mode == 0) {
                if (alive) {
                    if (n == 2 || n == 3) next[i][j] = 1;
                }
                else {
                    if (n == 3) next[i][j] = 1;
                }
            }
            else {
                if (alive) {
                    if (n == 1 || n == 3 || n == 5) next[i][j] = 1;
                }
                else {
                    if (n == 2 || n == 4) next[i][j] = 1;
                }
            }
        }
    }
    return next;
}

void placeGlider(vector<vector<int>>& grid, int r, int c) {
    int rows = grid.size(), cols = grid[0].size();
    grid[(r + 0) % rows][(c + 1) % cols] = 1;
    grid[(r + 1) % rows][(c + 2) % cols] = 1;
    grid[(r + 2) % rows][(c + 0) % cols] = 1;
    grid[(r + 2) % rows][(c + 1) % cols] = 1;
    grid[(r + 2) % rows][(c + 2) % cols] = 1;
}

void randomInit(vector<vector<int>>& grid, double density = 0.3) {
    int rows = grid.size(), cols = grid[0].size();
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            grid[i][j] = (rand() / double(RAND_MAX)) < density ? 1 : 0;
}


void number13() {
    srand(static_cast<unsigned>(time(0)));

    int rows = 20, cols = 50;
    int mode = 0;
    int steps = 200;

    cout << "Задача 3:\n";
    cout << "Выберите режим:\n0 - классические правила\n1 - альтерантивные\n";
    cin >> mode;

    vector<vector<int>> grid(rows, vector<int>(cols, 0));

    cout << "Инициализация:\n1 - глайдер\n2 - случайные\n";
    int init;
    cin >> init;

    if (init == 1) {
        placeGlider(grid, rows / 2 - 1, cols / 2 - 2);
    }
    else if (init == 2) {
        randomInit(grid, 0.25);
    }
    else {
        cout << "Неверный выбор. По умолчанию случ\n";
        randomInit(grid, 0.2);
    }

    cout << "Симуляция\n";
    for (int gen = 0; gen < steps; gen++) {
        clearScreen();
        cout << "Поколение: " << gen << " | Режим: " << (mode ? "альтернативный" : "классический") << "\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << (grid[i][j] ? '0' : ' ');
            }
            cout << '\n';
        }
        grid = nextGen(grid, mode);
        
    }

    cout << "\nСимуляция завершена.\n\n";
}
