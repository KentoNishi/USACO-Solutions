// Test case path: [path]
// moop - Silver - US-Open 2019-2020
// http://usaco.org/index.php?page=viewproblem&cpid=1028

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x;
    int y;
};

int main() {
    ifstream fin("moop.in");
    ofstream fout("moop.out");
    int N;
    fin >> N;
    vector<Point> points = vector<Point>(N);
    for (int i = 0; i < N; i++) {
        fin >> points[i].x >> points[i].y;
    }
    sort(points.begin(), points.end(), [](Point a, Point b) {
        return (a.x == b.x ? (a.y < b.y) : (a.x < b.x));
    });
    vector<int> maxToRight = vector<int>(N);
    vector<int> minToLeft = maxToRight;
    minToLeft[0] = points[0].y;
    maxToRight[N - 1] = points[N - 1].y;
    for (int i = 1; i < N; i++) {
        minToLeft[i] = min(minToLeft[i - 1], points[i].y);
    }
    for (int i = N - 2; i >= 0; i--) {
        maxToRight[i] = max(maxToRight[i + 1], points[i].y);
    }
    int ans = 1;
    for (int i = 0; i < N - 1; i++) {
        if (minToLeft[i] > maxToRight[i + 1]) {
            ans++;
        }
    }
    fout << ans << endl;
    return 0;
}