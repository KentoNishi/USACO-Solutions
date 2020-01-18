// Test case path: [path]
// perimeter - Silver - January 2018-2019
// http://usaco.org/index.php?page=viewproblem2&cpid=895

#include <bits/stdc++.h>
using namespace std;

int N;
vector<vector<bool>> grid;
vector<vector<bool>> visited;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

pair<int, int> floodFill(int x, int y) {
    if (x >= N || y >= N | x < 0 || y < 0 || visited[x][y] || !grid[x][y]) {
        return {0, 0};
    }
    visited[x][y] = true;
    int area = 1;
    int perim = 4;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= N || ny >= N | nx < 0 || ny < 0) {
            continue;
        }
        if (grid[nx][ny]) {
            perim--;
        }
        pair<int, int> result = floodFill(nx, ny);
        area += result.first;
        perim += result.second;
    }
    return {area, perim};
}

int main() {
    ifstream fin("perimeter.in");
    ofstream fout("perimeter.out");
    fin >> N;
    grid = vector<vector<bool>>(N, vector<bool>(N));
    visited = grid;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char c;
            fin >> c;
            grid[i][j] = c == '#';
        }
    }
    int maxArea = 0;
    int perimeter = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!visited[i][j]) {
                pair<int, int> result = floodFill(i, j);
                if (result.first > maxArea) {
                    maxArea = result.first;
                    perimeter = result.second;
                } else if (result.first == maxArea) {
                    if (result.second < perimeter) {
                        perimeter = result.second;
                    }
                }
            }
        }
    }
    fout << maxArea << " " << perimeter << endl;
    return 0;
}