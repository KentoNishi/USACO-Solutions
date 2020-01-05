// Test case path: [C:\Users\kento\Downloads\lightson_silver_dec15]
// lightson - Silver - December 2015-2016
// http://usaco.org/index.php?page=viewproblem2&cpid=570

#include <bits/stdc++.h>
using namespace std;

int N, M;

struct Pixel {
    bool on = false;
    bool visited = false;
    bool reachable = false;
    vector<pair<int, int>> switches = {};
};

vector<vector<Pixel>> grid;

int main() {
    ifstream fin("lightson.in");
    ofstream fout("lightson.out");
    fin >> N >> M;
    grid = vector<vector<Pixel>>(N, vector<Pixel>(N));
    for (int i = 0; i < M; i++) {
        int a, b, c, d;
        fin >> a >> b >> c >> d;
        a--;
        b--;
        c--;
        d--;
        grid[a][b].switches.push_back(make_pair(c, d));
    }
    grid[0][0].on = true;
    grid[0][0].reachable = true;
    grid[0][0].visited = true;
    queue<pair<int, int>> todo;
    todo.emplace(0, 0);
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    while (todo.size() > 0) {
        int x = todo.front().first;
        int y = todo.front().second;
        todo.pop();
        for (int i = 0; i < 4; i++) {
            int nx = dx[i] + x;
            int ny = dy[i] + y;
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) {
                continue;
            }
            grid[nx][ny].reachable = true;
            if (grid[nx][ny].on && !grid[nx][ny].visited) {
                todo.emplace(nx, ny);
                grid[nx][ny].visited = true;
            }
        }
        for (auto &point : grid[x][y].switches) {
            int nx = point.first;
            int ny = point.second;
            grid[nx][ny].on = true;
            if (!grid[nx][ny].visited && grid[nx][ny].reachable) {
                todo.emplace(nx, ny);
                grid[nx][ny].visited = true;
            }
        }
    }
    int ans = 0;
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            if (grid[x][y].on) {
                ans++;
            }
        }
    }
    fout << ans << endl;
    return 0;
}