// helpcross - Silver - February 2016-2017
// http://usaco.org/index.php?page=viewproblem2&cpid=714

#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("helpcross.in");
    ofstream fout("helpcross.out");
    int C, N;
    fin >> C >> N;
    vector<int> chickens = vector<int>(C);
    vector<pair<int, int>> cows = vector<pair<int, int>>(N);
    for (int i = 0; i < C; i++) {
        fin >> chickens[i];
    }
    for (int i = 0; i < N; i++) {
        fin >> cows[i].first >> cows[i].second;
    }
    sort(chickens.begin(), chickens.end());
    sort(cows.begin(), cows.end(), [](pair<int, int> a, pair<int, int> b) {
        return a.second < b.second;
    });
    int ans = 0;
    for (int i = 0; i < N; i++) {
        auto chickPointer = lower_bound(chickens.begin(), chickens.end(), cows[i].first);
        if (chickPointer != chickens.end() && *chickPointer <= cows[i].second) {
            ans++;
            chickens.erase(chickPointer);
        }
    }
    fout << ans << endl;
    return 0;
}