// Test case path: [path]
// mooyomooyo - Silver - December 2018-2019
// http://usaco.org/index.php?page=viewproblem2&cpid=860

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> grid;
int N, K;

void flood(int i, int j, int val, vector<vector<bool>> &visited, vector<pair<int, int>> &flooded) {
    if (i < 0 || i == N || j < 0 || j == 10) {
        return;
    }
    if (visited[i][j]) {
        return;
    }
    if (grid[i][j] != val) {
        return;
    }
    visited[i][j] = true;
    flooded.push_back(make_pair(i, j));
    vector<int> dx = {-1, 0, 1, 0};
    vector<int> dy = {0, 1, 0, -1};
    for (int m = 0; m < 4; m++) {
        flood(i + dy[m], j + dx[m], val, visited, flooded);
    }
}

void gravity() {
    for (int x = 0; x < 10; x++) {
        vector<int> nums;
        for (int y = N - 1; y >= 0; y--) {
            if (grid[y][x] != 0) {
                nums.push_back(grid[y][x]);
                grid[y][x] = 0;
            }
        }
        for (int y = N - 1; y >= N - nums.size(); y--) {
            grid[y][x] = nums[N - 1 - y];
        }
    }
}

int main() {
    ifstream fin("mooyomooyo.in");
    ofstream fout("mooyomooyo.out");
    fin >> N >> K;
    grid = vector<vector<int>>(N, vector<int>(10));
    for (int i = 0; i < N; i++) {
        string str;
        fin >> str;
        for (int j = 0; j < 10; j++) {
            grid[i][j] = str[j] - '0';
        }
    }
    bool done = false;
    while (!done) {
        done = true;
        vector<vector<bool>> visited = vector<vector<bool>>(N, vector<bool>(10));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < 10; j++) {
                if (grid[i][j] != 0) {
                    vector<pair<int, int>> flooded;
                    flood(i, j, grid[i][j], visited, flooded);
                    if (flooded.size() >= K) {
                        done = false;
                        for (auto &coord : flooded) {
                            grid[coord.first][coord.second] = 0;
                        }
                    }
                }
            }
        }
        gravity();
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 10; j++) {
            fout << grid[i][j];
        }
        fout << endl;
    }
    return 0;
}