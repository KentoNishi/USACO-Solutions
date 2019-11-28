// helpcross - Silver - February 2016-2017
// http://usaco.org/index.php?page=viewproblem2&cpid=714

#include <bits/stdc++.h>
using namespace std;

int C, N;
vector<int> chickens;
vector<pair<int, int>> cows;
struct compare {
    bool operator()(pair<int, int> a, pair<int, int> b) const {
        return a.second < b.second;
    }
};

int main() {
    ifstream fin("helpcross.in");
    ofstream fout("helpcross.out");
    fin >> C >> N;
    chickens = vector<int>(C);
    for (int i = 0; i < C; i++) {
        fin >> chickens[i];
    }
    cows = vector<pair<int, int>>(N);
    for (int i = 0; i < N; i++) {
        fin >> cows[i].first >> cows[i].second;
    }
    sort(chickens.begin(), chickens.end());
    sort(cows.begin(), cows.end(), compare());
    int ans = 0;
    for (int i = 0; i < cows.size(); i++) {
        auto chicken = lower_bound(chickens.begin(), chickens.end(), cows[i].first);
        if (chicken != chickens.end() && *chicken <= cows[i].second) {
            ans++;
            chickens.erase(chicken);
        }
    }
    fout << ans << endl;
    return 0;
}