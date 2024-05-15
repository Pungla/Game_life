#include <iostream>
#include <vector>
#include <windows.h>
#include <random>
using namespace std;

// ������� ��� ������ �������� ��������� ���� �� �����
void printGrid(const vector<vector<int>>& grid) {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            cout << (cell ? "O" : ".") << " "; // 'O' ��� ����� ������, '.' ��� ������
        }
        cout << endl;
    }
}

// ������� ��� �������� ���������� ����� ������� � ������ (i, j)
int countAliveNeighbors(const vector<vector<int>>& grid, int i, int j) {
    int count = 0;
    int rows = grid.size();
    int cols = grid[0].size();

    // ����� �������� ������
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            if (x == 0 && y == 0) continue; // ������� ����� ������
            int ni = i + x;
            int nj = j + y;
            if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                count += grid[ni][nj];
            }
        }
    }
    return count;
}

// ������� ��� ���������� ������ ���� ����
void nextGeneration(vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<vector<int>> newGrid = grid;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int aliveNeighbors = countAliveNeighbors(grid, i, j);

            if (grid[i][j] == 1) { // ����� ������
                if (aliveNeighbors < 2 || aliveNeighbors > 3) {
                    newGrid[i][j] = 0; // ������ �������
                }
            }
            else { // ̸����� ������
                if (aliveNeighbors == 3) {
                    newGrid[i][j] = 1; // ������ �������
                }
            }
        }
    }
    grid = newGrid; // ��������� �����
}

// ������� ��� ���������� ���� ���������� ����������
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
    // ������������� ���� �������� 50x50
    const int rows = 30;
    const int cols = 30;
    vector<vector<int>> grid(rows, vector<int>(cols, 0));

    // ���������� ���� ���������� ����������
    randomizeGrid(grid);

    // �������� ���� ����
    while (true) {
        printGrid(grid); // ����� �������� ��������� ����
        nextGeneration(grid); // ������� � ���������� ���������
        //delay(10000);
        Sleep(1000); // �������� � 200 �����������
        cout << "\033[H\033[J"; // ������� ������
    }

    return 0;
}
