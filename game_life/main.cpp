#include <iostream>
#include <vector>
#include <windows.h>
#include <random>
using namespace std;

// Функция для вывода текущего состояния поля на экран
void printGrid(const vector<vector<int>>& grid) {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            cout << (cell ? "O" : ".") << " "; // 'O' для живой клетки, '.' для мёртвой
        }
        cout << endl;
    }
}

// Функция для подсчёта количества живых соседей у клетки (i, j)
int countAliveNeighbors(const vector<vector<int>>& grid, int i, int j) {
    int count = 0;
    int rows = grid.size();
    int cols = grid[0].size();

    // Обход соседних клеток
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            if (x == 0 && y == 0) continue; // Пропуск самой клетки
            int ni = i + x;
            int nj = j + y;
            if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                count += grid[ni][nj];
            }
        }
    }
    return count;
}

// Функция для выполнения одного шага игры
void nextGeneration(vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<vector<int>> newGrid = grid;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int aliveNeighbors = countAliveNeighbors(grid, i, j);

            if (grid[i][j] == 1) { // Живая клетка
                if (aliveNeighbors < 2 || aliveNeighbors > 3) {
                    newGrid[i][j] = 0; // Клетка умирает
                }
            }
            else { // Мёртвая клетка
                if (aliveNeighbors == 3) {
                    newGrid[i][j] = 1; // Клетка оживает
                }
            }
        }
    }
    grid = newGrid; // Обновляем сетку
}

// Функция для заполнения поля случайными значениями
void randomizeGrid(vector<vector<int>>& grid) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);

    for (auto& row : grid) {
        for (int& cell : row) {
            cell = dis(gen);
        }
    }
}

int main() {
    // Инициализация поля размером 50x50
    const int rows = 30;
    const int cols = 30;
    vector<vector<int>> grid(rows, vector<int>(cols, 0));

    // Заполнение поля случайными значениями
    randomizeGrid(grid);

    // Основной цикл игры
    while (true) {
        printGrid(grid); // Вывод текущего состояния поля
        nextGeneration(grid); // Переход к следующему поколению
        //delay(10000);
        Sleep(1000); // Задержка в 200 миллисекунд
        cout << "\033[H\033[J"; // Очистка экрана
    }

    return 0;
}
