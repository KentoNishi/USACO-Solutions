// Test case path: [path]
// gates - Division - Month Season
// http://usaco.org/index.php?page=viewproblem2&cpid=596

#include <bits/stdc++.h>
using namespace std;

int N;

struct Pixel {
    map<pair<int, int>, bool> blocked;
    bool visited;
    int id = 0;
};

vector<vector<Pixel>> grid;

void floodFill(int x, int y, int id) {
    if (x == -1 || y == -1 || x == 2 * N + 1 || y == 2 * N + 1) {
        return;
    }
    if (grid[x][y].visited) {
        return;
    }
    grid[x][y].id = id;
    grid[x][y].visited = true;
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    for (int i = 0; i < 4; i++) {
        if (x + dx[i] == -1 || y + dy[i] == -1 || x + dx[i] == 2 * N + 1 || y + dy[i] == 2 * N + 1) {
            continue;
        }
        if (!grid[x][y].blocked[make_pair(x + dx[i], y + dy[i])]) {
            floodFill(x + dx[i], y + dy[i], id);
        }
    }
}

int main() {
    ifstream fin("gates.in");
    ofstream fout("gates.out");
    fin >> N;
    grid = vector<vector<Pixel>>(2 * N + 1, vector<Pixel>(2 * N + 1));
    string s;
    fin >> s;
    int x = N;
    int y = N;
    for (int i = 0; i < s.size(); i++) {
        switch (s[i]) {
        case 'N': {
            grid[x][y - 1].blocked[make_pair(x - 1, y - 1)] = true;
            grid[x - 1][y - 1].blocked[make_pair(x, y - 1)] = true;
            y--;
            break;
        }

        case 'S': {
            grid[x][y].blocked[make_pair(x - 1, y)] = true;
            grid[x - 1][y].blocked[make_pair(x, y)] = true;
            y++;
            break;
        }

        case 'E': {
            grid[x][y].blocked[make_pair(x, y - 1)] = true;
            grid[x][y - 1].blocked[make_pair(x, y)] = true;
            x++;
            break;
        }

        case 'W': {
            grid[x - 1][y].blocked[make_pair(x - 1, y - 1)] = true;
            grid[x - 1][y - 1].blocked[make_pair(x - 1, y)] = true;
            x--;
            break;
        }
        } /*
        for (int y1 = 0; y1 < 2 * N + 1; y1++) {
            for (int x1 = 0; x1 < 2 * N + 1; x1++) {
                if (y1 < 2 * N && grid[x1][y1].blocked[x1][y1 + 1]) {
                    cout << "\033[4m"
                         << (x1 == x && y1 == y ? "#" : "`") << "\033[0m";
                } else {
                    cout << (x1 == x && y1 == y ? "#" : "`");
                }

                if (x1 < 2 * N && grid[x1][y1].blocked[x1 + 1][y1]) {
                    cout << "|";
                } else {
                    cout << " ";
                }
            }
            cout << endl;
        }
        for (int x1 = 0; x1 < 2 * N + 1; x1++) {
            cout << " =";
        }
        cout << endl;*/
    }
    int count = 0;
    int id = 1;
    for (int y = 0; y < 2 * N + 1; y++) {
        for (int x = 0; x < 2 * N + 1; x++) {
            if (!grid[x][y].visited) {
                floodFill(x, y, id++);
                count++;
            }
        }
    }
    fout << count - 1 << endl;
    return 0;
}