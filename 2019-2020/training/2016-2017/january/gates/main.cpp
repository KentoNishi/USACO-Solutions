// Test case path: [path]
// gates - Division - Month Season
// http://usaco.org/index.php?page=viewproblem2&cpid=596

#include <bits/stdc++.h>
using namespace std;

int N;

struct Pixel {
    vector<pair<int, int>> blocked;
    bool visited;
    int id = 0;
};

vector<vector<Pixel>> grid;
int h = 0;
int w = 0;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
void floodFill(int x, int y, int id) {
    if (x == -1 || y == -1 || x == w || y == h) {
        return;
    }
    if (grid[x][y].visited) {
        return;
    }
    grid[x][y].id = id;
    grid[x][y].visited = true;
    for (int i = 0; i < 4; i++) {
        if (x + dx[i] == -1 || y + dy[i] == -1 || x + dx[i] == w || y + dy[i] == h) {
            continue;
        }
        if (find(grid[x][y].blocked.begin(), grid[x][y].blocked.end(), make_pair(x + dx[i], y + dy[i])) == grid[x][y].blocked.end()) {
            floodFill(x + dx[i], y + dy[i], id);
        }
    }
}

int main() {
    ifstream fin("gates.in");
    ofstream fout("gates.out");
    fin >> N;
    string s;
    fin >> s;
    /*
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    */
    for (int i = 0; i < s.size(); i++) {
        switch (s[i]) {
        case 'N': {
            h++;
        }

        case 'S': {
            h--;
        }

        case 'E': {
            w++;
        }

        case 'W': {
            w--;
        }
        }
    }
    w = 2 * abs(w) + 2;
    h = 2 * abs(h) + 2;
    grid = vector<vector<Pixel>>(w, vector<Pixel>(h));
    int x = w / 2;
    int y = w / 2;
    for (int i = 0; i < N; i++) {
        switch (s[i]) {
        case 'N': {
            grid[x][y - 1].blocked.push_back(make_pair(x - 1, y - 1));
            grid[x - 1][y - 1].blocked.push_back(make_pair(x, y - 1));
            y--;
            break;
        }

        case 'S': {
            grid[x][y].blocked.push_back(make_pair(x - 1, y));
            grid[x - 1][y].blocked.push_back(make_pair(x, y));
            y++;
            break;
        }

        case 'E': {
            grid[x][y].blocked.push_back(make_pair(x, y - 1));
            grid[x][y - 1].blocked.push_back(make_pair(x, y));
            x++;
            break;
        }

        case 'W': {
            grid[x - 1][y].blocked.push_back(make_pair(x - 1, y - 1));
            grid[x - 1][y - 1].blocked.push_back(make_pair(x - 1, y));
            x--;
            break;
        }
        }
        /*
        for (int y1 = 0; y1 < h; y1++) {
            for (int x1 = 0; x1 < w; x1++) {
                if (y1 < h && find(grid[x1][y1].blocked.begin(), grid[x1][y1].blocked.end(), make_pair(x1, y1 + 1)) != grid[x1][y1].blocked.end()) {
                    cout << "\033[4m"
                         << (x1 == x && y1 == y ? "#" : "`") << "\033[0m";
                } else {
                    cout << (x1 == x && y1 == y ? "#" : "`");
                }

                if (x1 < w && find(grid[x1][y1].blocked.begin(), grid[x1][y1].blocked.end(), make_pair(x1 + 1, y1)) != grid[x1][y1].blocked.end()) {
                    cout << "|";
                } else {
                    cout << " ";
                }
            }
            cout << endl;
        }
        for (int x1 = 0; x1 < w; x1++) {
            cout << " =";
        }
        cout << endl;*/
    }
    int count = 0;
    int id = 1;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (!grid[x][y].visited) {
                floodFill(x, y, id++);
                count++;
            }
        }
    }
    fout << count - 1 << endl;
    return 0;
}