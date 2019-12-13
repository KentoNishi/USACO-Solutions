// Test case path: [path]
// gates - Division - Month Season
// http://usaco.org/index.php?page=viewproblem2&cpid=596

#include <bits/stdc++.h>
using namespace std;

int N;
map<pair<pair<int, int>, pair<int, int>>, bool> blocked;

void floodFill(int x, int y, vector<vector<bool>> &visited) {
    if (x == 2 * N + 1 || y == 2 * N + 1 || x == -1 || y == -1) {
        return;
    }
    if (visited[x][y]) {
        return;
    }
    visited[x][y] = true;
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    for (int i = 0; i < 4; i++) {
        if (x + dx[i] == 2 * N + 1 || y + dy[i] == 2 * N + 1 || x + dx[i] == -1 || y + dy[i] == -1) {
            continue;
        }
        if (!blocked[make_pair(make_pair(x, y), make_pair(x + dx[i], y + dy[i]))]) {
            floodFill(x + dx[i], y + dy[i], visited);
        }
    }
}

int main() {
    ifstream fin("gates.in");
    ofstream fout("gates.out");
    fin >> N;
    int x = N;
    int y = N;
    string s;
    fin >> s;
    for (auto &c : s) {
        if (c == 'N') {
            blocked[make_pair(make_pair(x, y), make_pair(x, y - 1))] = true;
            blocked[make_pair(make_pair(x, y - 1), make_pair(x, y))] = true;
            y--;
        }
        if (c == 'S') {
            blocked[make_pair(make_pair(x, y), make_pair(x, y + 1))] = true;
            blocked[make_pair(make_pair(x, y + 1), make_pair(x, y))] = true;
            y++;
        }
        if (c == 'W') {
            blocked[make_pair(make_pair(x, y), make_pair(x - 1, y))] = true;
            blocked[make_pair(make_pair(x - 1, y), make_pair(x, y))] = true;
            x--;
        }
        if (c == 'E') {
            blocked[make_pair(make_pair(x, y), make_pair(x + 1, y))] = true;
            blocked[make_pair(make_pair(x + 1, y), make_pair(x, y))] = true;
            x++;
        }
    }
    for (auto &p : blocked) {
        // cout << p.first.first.first << "," << p.first.first.second << " cannot access " << p.first.second.first << "," << p.first.second.second << endl;
    }

    vector<vector<bool>> visited = vector<vector<bool>>(2 * N + 1, vector<bool>(2 * N + 1));
    int count = 0;
    for (int x = 0; x <= 2 * N; x++) {
        for (int y = 0; y <= 2 * N; y++) {
            if (!visited[x][y]) {
                // cout << x << "," << y << " is valid " << endl;
                floodFill(x, y, visited);
                count++;
            }
        }
    }
    fout << count << endl;
    return 0;
}