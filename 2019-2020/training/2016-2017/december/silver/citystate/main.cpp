// citystate - Silver - December 2016-2017
// http://usaco.org/index.php?page=viewproblem2&cpid=667

#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("citystate.in");
    ofstream fout("citystate.out");
    int N;
    fin >> N;
    vector<pair<string, string>> locs = vector<pair<string, string>>(N);
    // <city, state>
    for (int i = 0; i < N; i++) {
        fin >> locs[i].first >> locs[i].second;
        locs[i].first = locs[i].first.substr(0, 2);
    }
    map<pair<string, string>, int> locMap;
    for (auto &loc : locs) {
        if (loc.first != loc.second) {
            locMap[make_pair(loc.first, loc.second)]++;
        }
    }
    int total = 0;
    for (auto &loc : locs) {
        if (locMap[make_pair(loc.second, loc.first)] > 0 && locMap[make_pair(loc.first, loc.second)] > 0) {
            total += locMap[make_pair(loc.second, loc.first)] * locMap[make_pair(loc.first, loc.second)];
            locMap[make_pair(loc.first, loc.second)] = 0;
        }
    }
    fout << total << endl;
    return 0;
}