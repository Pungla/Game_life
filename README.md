# Conway's Game of Life on C++

This project is an implementation of Conway's Game of Life, a cellular automaton devised by mathematician John Horton Conway.

## Overview

The Game of Life is a zero-player game that evolves over time according to its initial state. The game consists of a grid of cells that can be alive or dead. Each cell's state changes in discrete steps based on the number of alive neighbors it has. The rules for the state changes are simple but lead to complex and fascinating patterns.

## Features

- Random initialization of the grid
- Continuous updating of the grid based on the Game of Life rules
- Visualization of the grid in the console

## How It Works

The main components of the program are:

### 1. Grid Initialization

The grid is initialized to a fixed size (30x30) and populated with random values, where each cell can be either alive (1) or dead (0).

```cpp
const int rows = 30;
const int cols = 30;
vector<vector<int>> grid(rows, vector<int>(cols, 0));
randomizeGrid(grid);
```

### 2. Printing the Grid

The `printGrid` function displays the current state of the grid in the console. Alive cells are represented by 'O', and dead cells by '.'.

```cpp
void printGrid(const vector<vector<int>>& grid) {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            cout << (cell ? "O" : ".") << " ";
        }
        cout << endl;
    }
}
```

### 3. Counting Alive Neighbors

The `countAliveNeighbors` function calculates the number of alive neighbors for a given cell.

```cpp
int countAliveNeighbors(const vector<vector<int>>& grid, int i, int j) {
    int count = 0;
    int rows = grid.size();
    int cols = grid[0].size();
    // Neighboring cells count
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            if (x == 0 && y == 0) continue; // Skip the cell itself
            int ni = i + x;
            int nj = j + y;
            if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                count += grid[ni][nj];
            }
        }
    }
    return count;
}
```

### 4. Updating the Grid

The `nextGeneration` function updates the grid to the next generation based on the Game of Life rules:

- Any live cell with fewer than two live neighbors dies (underpopulation).
- Any live cell with two or three live neighbors lives on to the next generation.
- Any live cell with more than three live neighbors dies (overpopulation).
- Any dead cell with exactly three live neighbors becomes a live cell (reproduction).

```cpp
void nextGeneration(vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<vector<int>> newGrid = grid;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int aliveNeighbors = countAliveNeighbors(grid, i, j);
            if (grid[i][j] == 1) {
                if (aliveNeighbors < 2 || aliveNeighbors > 3) {
                    newGrid[i][j] = 0;
                }
            } else {
                if (aliveNeighbors == 3) {
                    newGrid[i][j] = 1;
                }
            }
        }
    }
    grid = newGrid;
}
```

### 5. Main Loop

The `main` function initializes the grid, randomizes it, and runs the game in a continuous loop, updating the grid and printing it to the console.

```cpp
int main() {
    const int rows = 30;
    const int cols = 30;
    vector<vector<int>> grid(rows, vector<int>(cols, 0));

    randomizeGrid(grid);

    while (true) {
        printGrid(grid);
        nextGeneration(grid);
        Sleep(1000); // Delay in milliseconds
        cout << "\033[H\033[J"; // Clear screen
    }

    return 0;
}
```

## Getting Started

### Prerequisites

- C++ compiler
- Windows OS (for `Sleep` function and `windows.h` library)
