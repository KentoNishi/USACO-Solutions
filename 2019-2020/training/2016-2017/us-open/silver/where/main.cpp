// Test case path: [C:\Users\kento\OneDrive\Files\Downloads\where_silver_open17]
// where - Silver - US-Open 2016-2017
// http://usaco.org/index.php?page=viewproblem2&cpid=740

#include <bits/stdc++.h>
using namespace std;

struct Pixel {
    char value;
    bool visited = false;
};

struct PCL {
    int minX, minY, maxX, maxY;
};

int N;
vector<vector<Pixel>> grid;
vector<PCL> pcls;

void visit(int x, int y, int minX, int minY, int maxX, int maxY, char value) {
    if (x < minX || y < minY || x > maxX || y > maxY) {
        return;
    }
    if (grid[x][y].visited) {
        return;
    }
    if (grid[x][y].value != value) {
        return;
    }
    grid[x][y].visited = true;
    visit(x + 1, y, minX, minY, maxX, maxY, value);
    visit(x - 1, y, minX, minY, maxX, maxY, value);
    visit(x, y + 1, minX, minY, maxX, maxY, value);
    visit(x, y - 1, minX, minY, maxX, maxY, value);
}

bool isPCL(int minX, int minY, int maxX, int maxY) {
    map<char, int> colorCounts;
    for (int x = minX; x <= maxX; x++) {
        for (int y = minY; y <= maxY; y++) {
            grid[x][y].visited = false;
        }
    }
    for (int x = minX; x <= maxX; x++) {
        for (int y = minY; y <= maxY; y++) {
            if (!grid[x][y].visited) {
                colorCounts[grid[x][y].value]++;
                visit(x, y, minX, minY, maxX, maxY, grid[x][y].value);
            }
        }
    }
    if (colorCounts.size() == 2) {
        auto p = colorCounts.begin();
        int a = (*p).second;
        p++;
        int b = (*p).second;
        if (a > b) {
            swap(a, b);
        }
        if (a == 1 && b > 1) {
            return true;
        }
    }
    return false;
}

int biggestPCL(int index) {
    for (int i = 0; i < pcls.size(); i++) {
        if (i != index) {
            if (pcls[index].minX >= pcls[i].minX &&
                pcls[index].minY >= pcls[i].minY &&
                pcls[index].maxX <= pcls[i].maxX &&
                pcls[index].maxY <= pcls[i].maxY) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ifstream fin("where.in");
    ofstream fout("where.out");
    fin >> N;
    grid = vector<vector<Pixel>>(N, vector<Pixel>(N));
    for (int i = 0; i < N; i++) {
        string s;
        fin >> s;
        for (int j = 0; j < N; j++) {
            grid[i][j].value = s[j];
        }
    }
    for (int minX = 0; minX < N; minX++) {
        for (int minY = 0; minY < N; minY++) {
            for (int maxX = minX; maxX < N; maxX++) {
                for (int maxY = minY; maxY < N; maxY++) {
                    if (isPCL(minX, minY, maxX, maxY)) {
                        PCL pcl = {minX, minY, maxX, maxY};
                        pcls.push_back(pcl);
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < pcls.size(); i++) {
        if (biggestPCL(i)) {
            ans++;
        }
    }
    fout << ans << endl;
    return 0;
}