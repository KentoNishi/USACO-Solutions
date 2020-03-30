// Test case path: [path]
// moop - Division - Month Season
// http://usaco.org/index.php?page=viewproblem&cpid=1028

#include <bits/stdc++.h>
using namespace std;

vector<int> groups;
vector<pair<int, int>> particles;
int N;

void doFlood(int id, int part) {
    groups[part] = id;
    for (int i = 0; i < N; i++) {
        if (groups[i] != -1) {
            continue;
        }
        int x1 = particles[part].first;
        int x2 = particles[i].first;
        int y1 = particles[part].second;
        int y2 = particles[i].second;
        if ((x1 <= x2 && y1 <= y2) || (x2 <= x1 && y2 <= y1)) {
            doFlood(id, i);
        }
    }
}

int main() {
    ifstream fin("moop.in");
    ofstream fout("moop.out");
    fin >> N;
    particles = vector<pair<int, int>>(N);
    for (int i = 0; i < N; i++) {
        fin >> particles[i].first >> particles[i].second;
    }
    groups = vector<int>(N, -1);
    int num = 0;
    for (int i = 0; i < N; i++) {
        if (groups[i] != -1) {
            continue;
        }
        doFlood(num, i);
        num++;
    }
    fout << num << endl;
    return 0;
}