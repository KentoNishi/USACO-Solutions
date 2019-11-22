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

int reach(vector<Cow> &points, int cow) {
    if (points[cow].visited) {
        return 0;
    }
    points[cow].visited = true;
    int sum = 1;
    for (auto &e : points[cow].e) {
        sum += reach(points, e);
    }
    return sum;
}

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
    for (int i = 0; i < N; i++) {
        cout << points[i].x << ", " << points[i].y << ": ";
        for (auto &e : points[i].e) {
            cout << e << " ";
        }
        cout << endl;
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        ans = max(ans, reach(points, i));
        for (int i = 0; i < N; i++) {
            points[i].visited = false;
        }
    }
    fout << ans << endl;
    return 0;
}