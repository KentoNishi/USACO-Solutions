// countcross - Silver - February 2016-2017
// http://usaco.org/index.php?page=viewproblem2&cpid=716

#include <bits/stdc++.h>
using namespace std;

struct Loc {
    map<pair<int, int>, bool> adjacent;
    // pair<int,int>, true if not accessible without crossing
};

int N, K, R;
vector<vector<Loc>> grid;
vector<pair<int, int>> cows;

bool canGo(int x, int y, int end, vector<vector<bool>> &visited) {
    if (x >= N || y >= N || x < 0 || y < 0) {
        return false;
    }
    if (visited[x][y]) {
        return false;
    }
    visited[x][y] = true;
    if (cows[end].first == x && cows[end].second == y) {
        return true;
    }
    vector<int> dx = {-1, 0, 1, 0};
    vector<int> dy = {0, -1, 0, 1};
    for (int i = 0; i < 4; i++) {
        if (x + dx[i] >= N || y + dy[i] >= N || x + dx[i] < 0 || y + dy[i] < 0) {
            continue;
        }
        pair<int, int> p = {x + dx[i], y + dy[i]};
        if (!grid[x][y].adjacent[p] && canGo(x + dx[i], y + dy[i], end, visited)) {
            return true;
        }
    }
    return false;
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
        pair<int, int> p1 = {a, b};
        pair<int, int> p2 = {c, d};
        grid[p1.first][p1.second].adjacent[p2] = true;
        grid[p2.first][p2.second].adjacent[p1] = true;
    }
    cows = vector<pair<int, int>>(K);
    for (int i = 0; i < K; i++) {
        fin >> cows[i].first >> cows[i].second;
        cows[i].first--;
        cows[i].second--;
    }
    int ans = 0;
    for (int i = 0; i < K; i++) {
        for (int j = i + 1; j < K; j++) {
            vector<vector<bool>> visited = vector<vector<bool>>(N, vector<bool>(N));
            if (!canGo(cows[i].first, cows[i].second, j, visited)) {
                ans++;
            }
        }
    }
    fout << ans << endl;
    return 0;
}