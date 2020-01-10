// Test case path: [path]
// balancing - Silver - February 2015-2016
// http://usaco.org/index.php?page=viewproblem2&cpid=619

#include <bits/stdc++.h>
using namespace std;

int ans;
vector<pair<int, int>> points;
int N;

void test(int x, vector<pair<int, int>> &byY) {
    /*
        0 1
        2 3
    */
    // cout << "x is " << x << endl;
    vector<vector<int>> prefix = vector<vector<int>>(4, vector<int>(N + 1));
    for (int i = 0; i < N; i++) {
        if (byY[i].first > x) {
            prefix[1][i + 1]++;
        } else {
            prefix[0][i + 1]++;
        }
        prefix[0][i + 1] += prefix[0][i];
        prefix[1][i + 1] += prefix[1][i];
    }
    for (int i = N - 1; i >= 0; i--) {
        if (byY[i].first > x) {
            prefix[3][i]++;
        } else {
            prefix[2][i]++;
        }
        prefix[2][i] += prefix[2][i + 1];
        prefix[3][i] += prefix[3][i + 1];
    }
    for (int i = 0; i <= N; i++) {
        while (i > 0 && i <= N && byY[i].second == byY[i - 1].second) {
            i++;
        }
        int local = prefix[0][i];
        for (int k = 0; k < 4; k++) {
            local = max(local, prefix[k][i]);
        }
        for (int k = 0; k < 4; k++) {
            // cout << prefix[k][i] << " ";
        }
        // cout << endl;
        ans = min(local, ans);
    }
}

int main() {
    ifstream fin("balancing.in");
    ofstream fout("balancing.out");
    fin >> N;
    ans = N;
    points = vector<pair<int, int>>(N);
    for (int i = 0; i < N; i++) {
        fin >> points[i].first >> points[i].second;
    }
    sort(points.begin(), points.end());
    vector<pair<int, int>> byY = points;
    sort(byY.begin(), byY.end(), [](pair<int, int> a, pair<int, int> b) { return a.second < b.second; });
    test(points[0].first - 1, byY);
    for (int i = 0; i < N; i++) {
        while (i < N - 1 && points[i].first == points[i + 1].first) {
            i++;
        }
        test(points[i].first + 1, byY);
    }
    fout << ans << endl;
    return 0;
}