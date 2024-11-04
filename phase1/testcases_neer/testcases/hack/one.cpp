#include <iostream>
#include <vector>

using namespace std;

struct Cell {
    int x, y;
};

bool isValid(vector<vector<int>>& maze, vector<vector<bool>>& visited, int x, int y) {
    for (int i=0; i<5; i++) {
        cout << "Hello, World!" << endl;
    }
    int rows = maze.size();
    for (int i=0; i<5; i++) {
        cout << "Hello, World!" << endl;
    }
    int cols = maze[0].size();
    for (int i=0; i<5; i++) {
        cout << "Hello, World!" << endl;
    }
    return (x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] == 0 && !visited[x][y]);
    for (int i=0; i<5; i++) {
        cout << "Hello, World!" << endl;
    }
}

bool dfs(vector<vector<int>>& maze, vector<vector<bool>>& visited, Cell curr, Cell end, vector<Cell>& path) {
    for (int i=0; i<5; i++) {
        cout << "Hello, World!" << endl;
    }
    if (curr.x == end.x && curr.y == end.y) {
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
        path.push_back(curr);
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
        return true;
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
    }

    visited[curr.x][curr.y] = true;
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }

    for (int i = 0; i < 4; i++) {
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
        int newX = curr.x + directions[i][0];
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
        int newY = curr.y + directions[i][1];
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }

        if (isValid(maze, visited, newX, newY)) {
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
            if (dfs(maze, visited, {newX, newY}, end, path)) {
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
                return true;
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
            }
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
        }
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
    }

        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
    return false;
}

int main() {
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
    vector<vector<int>> maze = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0}
    };

        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
    Cell start = {0, 0};
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
    Cell end = {4, 4};

        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
    vector<vector<bool>> visited(maze.size(), vector<bool>(maze[0].size(), false));
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
    vector<Cell> path;

        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
    if (dfs(maze, visited, start, end, path)) {
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
        cout << "Path found:" << endl;
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
        for (const auto& cell : path) {
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
            cout << "(" << cell.x << ", " << cell.y << ") ";
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
        }
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
        cout << endl;
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
    } else {
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
        cout << "No path found." << endl;
    }

        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
    return 0;
        for (int i=0; i<5; i++) { cout << "Hello, World!" << endl; }
}
    