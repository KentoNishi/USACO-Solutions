// Test case path: [path]
// mountains - Silver - January 2018-2019
// http://usaco.org/index.php?page=viewproblem2&cpid=896

#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("mountains.in");
    ofstream fout("mountains.out");
    int N;
    fin >> N;
    vector<pair<int, int>> mountains;
    mountains.resize(N);
    for (int i = 0; i < N; i++) {
        int a, b;
        fin >> a >> b;
        mountains[i].first = a - b;
        mountains[i].second = a + b;
    }
    sort(mountains.begin(), mountains.end(), [](pair<int, int> a, pair<int, int> b) {
        if (a.first != b.first) {
            return a.first < b.first;
        } else {
            return a.second > b.second;
        }
    });
    int maxRight = mountains[0].second;
    int ans = 1;
    for (int i = 1; i < N; i++) {
        if (mountains[i].second > maxRight) {
            maxRight = mountains[i].second;
            ans++;
        }
    }
    fout << ans << endl;
    return 0;
}