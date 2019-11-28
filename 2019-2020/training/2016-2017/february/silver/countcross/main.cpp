// Test case path: [C:\Users\kento\OneDrive\Files\Downloads\countcross_silver_feb17]
// countcross - Silver - February 2016-2017
// http://usaco.org/index.php?page=viewproblem2&cpid=716

#include <bits/stdc++.h>
using namespace std;

struct Loc {
    vector<bool> adjacent;
    bool cow = false;
    // pair<int,int>, true if not accessible without crossing
};

int N, K, R;
vector<vector<Loc>> grid;
vector<pair<int, int>> cows;

int cowsInRegion(int x, int y, vector<vector<bool>> &visited) {
    if (x >= N || y >= N || x < 0 || y < 0) {
        return 0;
    }
    if (visited[x][y]) {
        return 0;
    }
    visited[x][y] = true;
    vector<int> dx = {-1, 0, 0, 1};
    vector<int> dy = {0, -1, 1, 0};
    int sum = grid[x][y].cow ? 1 : 0;
    for (int i = 0; i < 4; i++) {
        if (!grid[x][y].adjacent[i]) {
            sum += cowsInRegion(x + dx[i], y + dy[i], visited);
        }
    }
    return sum;
}

int main() {
    ifstream fin("countcross.in");
    ofstream fout("countcross.out");
    fin >> N >> K >> R;
    // grid dimentions
    // number of cows
    // number of roads
    grid = vector<vector<Loc>>(N, vector<Loc>(N));
    for (int i = 0; i < R; i++) {
        int a, b, c, d;
        fin >> a >> b >> c >> d;
        a--;
        b--;
        c--;
        d--;
        vector<int> dx = {-1, 0, 0, 1};
        vector<int> dy = {0, -1, 1, 0};
        if (a - c == 1) {
            grid[a][b].adjacent[0] = true;
            grid[c][d].adjacent[3] = true;
        } else if (c - a == 1) {
            grid[a][b].adjacent[3] = true;
            grid[c][d].adjacent[0] = true;
        }
        if (b - d == 1) {
            grid[a][b].adjacent[1] = true;
            grid[c][d].adjacent[2] = true;
        } else if (d - b == 1) {
            grid[a][b].adjacent[2] = true;
            grid[c][d].adjacent[1] = true;
        }
    }
    cows = vector<pair<int, int>>(K);
    for (int i = 0; i < K; i++) {
        fin >> cows[i].first >> cows[i].second;
        cows[i].first--;
        cows[i].second--;
        grid[cows[i].first][cows[i].second].cow = true;
    }
    int ans = 0;
    vector<vector<bool>> visited = vector<vector<bool>>(N, vector<bool>(N));
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            int reg = cowsInRegion(x, y, visited);
            ans += (K - reg) * reg;
        }
    }
    fout << ans / 2 << endl;
    return 0;
}