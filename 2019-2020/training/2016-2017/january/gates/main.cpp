// Test case path: [path]
// gates - Division - Month Season
// http://usaco.org/index.php?page=viewproblem2&cpid=596

#include <bits/stdc++.h>
using namespace std;

int N;

struct Node {
    vector<bool> canGo;
};

vector<vector<int>> grid;
vector<Node> graph;
void floodFill(int x, int y, vector<vector<bool>> &visited, int id) {
    if (x == 2 * N + 1 || y == 2 * N + 1 || x == -1 || y == -1) {
        return;
    }
    if (visited[x][y]) {
        return;
    }
    if (grid[x][y] == 1) {
        return;
    }
    visited[x][y] = true;
    grid[x][y] = id;
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    for (int i = 0; i < 4; i++) {
        floodFill(x + dx[i], y + dy[i], visited, id);
    }
    return;
}

int main() {
    ifstream fin("gates.in");
    ofstream fout("gates.out");
    fin >> N;
    grid = vector<vector<int>>(2 * N + 1, vector<int>(2 * N + 1));
    int x = N;
    int y = N;
    string s;
    fin >> s;
    grid[x][y] = 1;
    for (auto &c : s) {
        if (c == 'N') {
            y--;
        }
        if (c == 'S') {
            y++;
        }
        if (c == 'W') {
            x--;
        }
        if (c == 'E') {
            x++;
        }
        grid[x][y] = 1;
    }
    int id = 2;
    vector<vector<bool>> visited = vector<vector<bool>>(2 * N + 1, vector<bool>(2 * N + 1));
    for (int x = 0; x <= 2 * N; x++) {
        for (int y = 0; y <= 2 * N; y++) {
            if (!visited[x][y] && grid[x][y] == 0) {
                graph.push_back(Node());
                floodFill(x, y, visited, id);
                id++;
            }
        }
    }
    fout << id - 2 << endl;

    return 0;
}