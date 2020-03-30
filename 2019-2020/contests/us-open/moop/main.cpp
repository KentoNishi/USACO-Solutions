// Test case path: [path]
// moop - Division - Month Season
// http://usaco.org/index.php?page=viewproblem&cpid=1028

#include <bits/stdc++.h>
using namespace std;

vector<int> groups;
vector<pair<int, int>> particles;
int N;
// N^2 solution, getting points first to get 833
// just in case I can't solve it

void doFlood(int id, int part) {
    groups[part] = id;
    for (int i = 0; i < N; i++) {
        if (groups[i] != -1) {
            continue;
        }
        double dy = particles[part].second - particles[i].second;
        double dx = particles[part].first - particles[i].first;
        if (particles[part].first == particles[i].first || dy / dx >= -1e-4) {
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