// where - Division - Month Season
// http://usaco.org/index.php?page=viewproblem2&cpid=740

#include <bits/stdc++.h>
using namespace std;

struct Pixel {
    char value;
    int region;
    bool seen;
};
int N = 0;

struct Region {
    int minX;
    int minY;
    int maxX;
    int maxY;
};

vector<vector<Pixel>> grid;

void markRegions(int x, int y, char value, int region) {
    if (x < 0 || y < 0 || x >= N || y >= N) {
        return;
    }
    if (grid[x][y].seen) {
        return;
    }
    if (grid[x][y].value != value) {
        return;
    }
    grid[x][y].seen = true;
    grid[x][y].region = region;
    markRegions(x + 1, y, value, region);
    markRegions(x - 1, y, value, region);
    markRegions(x, y + 1, value, region);
    markRegions(x, y - 1, value, region);
    return;
}

int inPCL(int xB, int yB, int xS, int yS, vector<Region> selected, int id) {
    for (int i = 0; i < selected.size(); i++) {
        auto r = selected[i];
        if (id != i && r.maxX >= xB && r.maxY >= yB && r.minX <= xS && r.minY <= yS) {
            //cout << r.minX << " " << r.minY << " " << r.maxX << " " << r.maxY << " was a match" << endl;
            return i;
        }
    }
    return -1;
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
    int region = 0;
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            if (!grid[x][y].seen) {
                //regions.push_back(Region());
                markRegions(x, y, grid[x][y].value, region);
                region++;
            }
        }
    } /*
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            cout << grid[x][y].region << " ";
        }
        cout << endl;
    }*/

    int ans = 0;
    vector<Region> selected;
    for (int xS = 0; xS < N; xS++) {
        for (int yS = 0; yS < N; yS++) {
            for (int xB = xS; xB < N; xB++) {
                for (int yB = yS; yB < N; yB++) {
                    map<char, set<int>> counts;
                    for (int x = xS; x <= xB; x++) {
                        for (int y = yS; y <= yB; y++) {
                            counts[grid[x][y].value].insert(grid[x][y].region);
                        }
                    }
                    if (counts.size() == 2) {
                        auto p = counts.begin();
                        int a = (*p).second.size();
                        p++;
                        int b = (*p).second.size();
                        if (a == 1 && b >= 2 || b == 1 && a >= 2) {
                            //cout << "!!! Choosing " << xS << " " << yS << " " << xB << " " << yB << endl;
                            selected.push_back(Region());
                            selected[selected.size() - 1].maxX = xB;
                            selected[selected.size() - 1].maxY = yB;
                            selected[selected.size() - 1].minX = xS;
                            selected[selected.size() - 1].minY = yS;
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < selected.size(); i++) {
        auto r = selected[i];
        //cout << "selected: " << r.minX << " " << r.minY << " " << r.maxX << " " << r.maxY << endl;
        int res = inPCL(r.maxX, r.maxY, r.minX, r.minY, selected, i);
        if (res == -1) {
            cout << r.minX << " " << r.minY << " " << r.maxX << " " << r.maxY << " is final" << endl;
            ans++;
        } else {
        }
    }
    fout << ans << endl;
    return 0;
}