#include <iostream>
#include <vector>

using namespace std;

void func1() {}
void func2() {}
void func3() {}
void func4() {}
void func5() {}
void func6() {}
void func7() {}
void func8() {}
void func9() {}
void func10() {}

struct Cell {
    int x, y;
};

bool isValid(vector<vector<int>>& maze, vector<vector<bool>>& visited, int x, int y) {
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
    int rows = maze.size();
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
    int cols = maze[0].size();
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
    return (x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] == 0 && !visited[x][y]);
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
}

bool dfs(vector<vector<int>>& maze, vector<vector<bool>>& visited, Cell curr, Cell end, vector<Cell>& path) {
    
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
    if (curr.x == end.x && curr.y == end.y) {
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
        path.push_back(curr);
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
        return true;
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
    }

    visited[curr.x][curr.y] = true;
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();

    for (int i = 0; i < 4; i++) {
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
        int newX = curr.x + directions[i][0];
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
        int newY = curr.y + directions[i][1];
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();

        if (isValid(maze, visited, newX, newY)) {
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
            if (dfs(maze, visited, {newX, newY}, end, path)) {
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
                path.push_back(curr);
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
                return true;
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
            }
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
        }
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
    }
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();

    return false;
}

int main() {
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
    vector<vector<int>> maze = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0}
    };
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();

    Cell start = {0, 0};
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
    Cell end = {4, 4};
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();

    vector<vector<bool>> visited(maze.size(), vector<bool>(maze[0].size(), false));
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
    vector<Cell> path;
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();

    if (dfs(maze, visited, start, end, path)) {
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
        cout << "Path found:" << endl;
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
        for (const auto& cell : path) {
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
            cout << "(" << cell.x << ", " << cell.y << ") ";
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
        }
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
        cout << endl;
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
    } else {
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
        cout << "No path found." << endl;
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();
    }
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func8();
    func9();
    func10();

    return 0;
}
