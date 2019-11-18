// multimoo - Silver - US-Open 2017-2018
// http://usaco.org/index.php?page=viewproblem2&cpid=836

#include <bits/stdc++.h>
using namespace std;

struct Cell {
    int cow;
    int region = -1;
    bool visited = false;
};

struct Region {
    int area = 0;
    int cow;
    set<int> adjacent;
    map<pair<int, int>, int> searched;
};

int N;

void floodAndMark(vector<vector<Cell>> &cells, int x, int y, int id, int cow) {
    if (x == N || y == N || x < 0 || y < 0) {
        return;
    }
    if (cells[x][y].region != -1) {
        return;
    }
    if (cells[x][y].cow != cow) {
        return;
    }
    cells[x][y].region = id;
    floodAndMark(cells, x + 1, y, id, cow);
    floodAndMark(cells, x - 1, y, id, cow);
    floodAndMark(cells, x, y + 1, id, cow);
    floodAndMark(cells, x, y - 1, id, cow);
}

int findAreas(vector<vector<Cell>> &cells, vector<Region> &regions, int x, int y, int id) {
    if (x == N || y == N || x < 0 || y < 0) {
        return 0;
    }
    if (cells[x][y].region != id) {
        regions[id].adjacent.insert(cells[x][y].region);
        return 0;
    }
    if (cells[x][y].visited) {
        return 0;
    }
    cells[x][y].visited = true;
    int area = 1;
    area += findAreas(cells, regions, x + 1, y, id);
    area += findAreas(cells, regions, x - 1, y, id);
    area += findAreas(cells, regions, x, y + 1, id);
    area += findAreas(cells, regions, x, y - 1, id);
    return area;
}

int floodDouble(vector<Region> &regions, int cow1, int cow2, int id, map<int, bool> &visited) {
    if (regions[id].cow != cow1 && regions[id].cow != cow2) {
        return 0;
    }
    if (visited[id]) {
        return 0;
    }
    if (regions[id].searched[make_pair(cow1, cow2)] > 0) {
        return regions[id].searched[make_pair(cow1, cow2)];
    }
    visited[id] = true;
    int area = regions[id].area;
    for (auto &adjacent : regions[id].adjacent) {
        area += floodDouble(regions, cow1, cow2, adjacent, visited);
    }
    regions[id].searched[make_pair(cow1, cow2)] = area;
    return area;
}

int main() {
    ofstream fout("multimoo.out");
    ifstream fin("multimoo.in");
    fin >> N;

    vector<vector<Cell>> cells = vector<vector<Cell>>(N, vector<Cell>(N));
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            fin >> cells[i][k].cow;
        }
    }

    int regionCount = 0;
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            if (cells[i][k].region == -1) {
                floodAndMark(cells, i, k, regionCount, cells[i][k].cow);
                regionCount++;
            }
        }
    }

    vector<Region> regions = vector<Region>(regionCount);
    int maxSingleArea = 0;
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            if (!cells[i][k].visited) {
                regions[cells[i][k].region].cow = cells[i][k].cow;
                regions[cells[i][k].region].area = findAreas(cells, regions, i, k, cells[i][k].region);
                maxSingleArea = max(maxSingleArea, regions[cells[i][k].region].area);
            }
        }
    }
    fout << maxSingleArea << endl;
    int maxDoubleArea = 0;
    for (int reg1 = 0; reg1 < regionCount; reg1++) {
        map<int, bool> visited;
        for (auto &reg2 : regions[reg1].adjacent) {
            maxDoubleArea = max(maxDoubleArea, floodDouble(regions, regions[reg1].cow, regions[reg2].cow, reg1, visited));
        }
    }
    fout << maxDoubleArea << endl;
    return 0;
}