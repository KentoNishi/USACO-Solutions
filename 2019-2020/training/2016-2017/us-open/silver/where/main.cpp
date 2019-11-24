// where - Division - Month Season
// url

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

void markRegions(int x, int y, int value, int region) {
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
    /*
    regions[region].maxX = max(regions[region].maxX, x);
    regions[region].maxY = max(regions[region].maxY, y);
    regions[region].minX = min(regions[region].minX, x);
    regions[region].minY = min(regions[region].minY, y);*/
    return;
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
    }
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            cout << grid[x][y].region << " ";
        }
        cout << endl;
    }

    int ans = 0;
    vector<Region> selected;
    for (int x1 = N - 1; x1 >= 0; x1--) {
        for (int y1 = N - 1; y1 >= 0; y1--) {
            for (int x2 = 0; x2 <= x1; x2++) {
                for (int y2 = 0; y2 <= y1; y2++) {
                    cout << "Coord: " << x2 << " " << y2 << " " << x1 << " " << y1 << endl;
                    map<char, set<int>> counts;
                    // pixel, region ids
                    bool exit = false;
                    for (auto &reg : selected) {
                        // mins: x2,y2
                        // maxs: x1, y1
                        if (x2 >= reg.minX && x1 <= reg.maxX && y2 >= reg.minY && y1 <= reg.maxY) {
                            exit = true;
                            break;
                        }
                    }
                    if (exit) {
                        continue;
                    }
                    for (int x3 = x2; x3 <= x1; x3++) {
                        for (int y3 = y2; y3 <= y1; y3++) {
                            counts[grid[x3][y3].value].insert(grid[x3][y3].region);
                        }
                    } /*
                    if(x2==0 && y2==2 && x1==3 && y1==3){
                        for(auto &m:counts){
                            cout << m.first << ": " << m.second.size() << endl;
                        }
                    }*/
                    if (counts.size() == 2) {
                        auto p = counts.begin();
                        int a = (*p).second.size();
                        p++;
                        int b = (*p).second.size();
                        if (a > b) {
                            swap(a, b);
                        }
                        if (a == 1 && b >= 2) { /*
                            cout << "!!! Choosing " << x2 << " " << y2 << " " << x1 << " " << y1 << endl;
                            for (auto &reg : selected) {
                                cout << "already selected: " << reg.minX << " " << reg.minY << " " << reg.maxX << " " << reg.maxY << endl;
                            }*/
                            selected.push_back(Region());
                            selected[selected.size() - 1].maxX = x1;
                            selected[selected.size() - 1].maxY = y1;
                            selected[selected.size() - 1].minX = x2;
                            selected[selected.size() - 1].minY = y2;
                            ans++;
                        }
                    }
                }
            }
        }
    }
    fout << ans << endl;

    /*
    for (int i = 0; i < region; i++) {
        cout << "region " << i << " has bounds " << regions[i].minX << " " << regions[i].minY << " " << regions[i].maxX << " " << regions[i].maxY << endl;
        map<char,set<int>> counts;
        // pixel value,regions of pixel value
        for(int x=regions[i].minX;x<=regions[i].maxX;x++){
            for(int y=regions[i].minY;y<=regions[i].maxY;y++){
                cout << "Investigating region " << i << " @ " << x << " " << y << endl;
                counts[grid[x][y].value].insert(i);
            }
        }
        cout << "resulted in " << counts.size() << endl;
        if(counts.size()==2){
            auto p=counts.begin();
            int a=(*p).second.size();
            p++;
            int b=(*p).second.size();
            if(a>b){
                swap(a,b);
            }
            if(a==1&&b>=2){
                ans++;
            }
        }
    }*/
    return 0;
}