#include <iostream>
#include <vector>
using namespace std;

class MazeSolver {
private:
    vector<vector<char>> maze;
    int rows, cols;
    // Direction arrays for moving in 4 directions (up, right, down, left)
    const int dx[4] = {-1, 0, 1, 0};
    const int dy[4] = {0, 1, 0, -1};
    
    bool isValid(int x, int y) {
        return (x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] != '#');
    }
    
    bool findPath(int x, int y, int endX, int endY) {
        // If we reached the end point
        if (x == endX && y == endY) {
            maze[x][y] = 'P';  // Mark as part of the path
            return true;
        }
        
        // If current cell is valid
        if (isValid(x, y)) {
            // Mark current cell as part of the path
            maze[x][y] = 'P';
            
            // Try all four directions
            for (int i = 0; i < 4; i++) {
                int newX = x + dx[i];
                int newY = y + dy[i];
                
                // If path found through this direction
                if (isValid(newX, newY) && maze[newX][newY] != 'P' && 
                    findPath(newX, newY, endX, endY)) {
                    return true;
                }
            }
            
            // If no path found through this cell, unmark it
            maze[x][y] = '.';
            return false;
        }
        return false;
    }

public:
    MazeSolver(vector<vector<char>>& m) : maze(m) {
        rows = maze.size();
        cols = maze[0].size();
    }
    
    bool solveMaze() {
        int startX = -1, startY = -1;
        int endX = -1, endY = -1;
        
        // Find start 'S' and end 'E' positions
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (maze[i][j] == 'S') {
                    startX = i;
                    startY = j;
                }
                if (maze[i][j] == 'E') {
                    endX = i;
                    endY = j;
                }
            }
        }
        
        // If start or end not found
        if (startX == -1 || endX == -1) {
            cout << "Start or end point not found in maze!" << endl;
            return false;
        }
        
        // Try to find a path
        if (findPath(startX, startY, endX, endY)) {
            printMaze();
            return true;
        }
        
        cout << "No path found!" << endl;
        return false;
    }
    
    void printMaze() {
        for (const auto& row : maze) {
            for (char cell : row) {
                cout << cell << ' ';
            }
            cout << endl;
        }
    }
};

int main() {
    // Example maze
    // S = Start, E = End, # = Wall, . = Open path
    vector<vector<char>> maze = {
        {'S', '.', '#', '#', '.', '.'},
        {'.', '.', '.', '.', '#', '.'},
        {'#', '.', '#', '.', '.', '.'},
        {'.', '#', '.', '#', '.', '#'},
        {'.', '.', '.', '.', '.', 'E'}
    };
    
    cout << "Original Maze:" << endl;
    for (const auto& row : maze) {
        for (char cell : row) {
            cout << cell << ' ';
        }
        cout << endl;
    }
    cout << endl;
    
    MazeSolver solver(maze);
    cout << "Solved Maze (P marks the path):" << endl;
    solver.solveMaze();
    
    return 0;
}