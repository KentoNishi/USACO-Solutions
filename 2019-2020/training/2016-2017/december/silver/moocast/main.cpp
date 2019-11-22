// moocast - Silver - December 2016-2017
// http://usaco.org/index.php?page=viewproblem2&cpid=668

#include <bits/stdc++.h>
using namespace std;

struct Cow {
    int x;
    int y;
    int r;
    vector<int> e;
    bool visited = false;
};

int main() {
    ifstream fin("moocast.in");
    ofstream fout("moocast.out");
    int N;
    fin >> N;
    vector<Cow> points = vector<Cow>(N);
    for (int i = 0; i < N; i++) {
        fin >> points[i].x >> points[i].y >> points[i].r;
    }
    for (int i = 0; i < N; i++) {
        for (int k = i + 1; k < N; k++) {
            float dist = sqrt(pow(points[i].x - points[k].x, 2) + pow(points[i].y - points[k].y, 2));
            if (dist <= points[i].r) {
                points[i].e.push_back(k);
            }
            if (dist <= points[k].r) {
                points[k].e.push_back(i);
            }
        }
    }
    return 0;
}