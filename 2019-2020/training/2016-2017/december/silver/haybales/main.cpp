// haybales - Silver - December 2016-2017
// http://usaco.org/index.php?page=viewproblem2&cpid=666

#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("haybales.in");
    ofstream fout("haybales.out");
    int N, Q;
    fin >> N >> Q;
    vector<int> locs = vector<int>(N);
    for (int i = 0; i < N; i++) {
        fin >> locs[i];
    }
    vector<pair<int, int>> queries = vector<pair<int, int>>(Q);
    for (int i = 0; i < Q; i++) {
        fin >> queries[i].first >> queries[i].second;
        if (queries[i].first > queries[i].second) {
            swap(queries[i].first, queries[i].second);
        }
    }
    sort(locs.begin(), locs.end());
    for (auto q : queries) {
        auto first = lower_bound(locs.begin(), locs.end(), q.first);
        auto second = upper_bound(locs.begin(), locs.end(), q.second);
        fout << abs(second - first) << endl;
    }
    return 0;
}