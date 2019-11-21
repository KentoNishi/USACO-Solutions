// citystate - Division - Month Season
// url

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
        locs[i].first = locs[i].first.substr(0,2);
    }
    map<pair<string, string>, pair<int,bool>> locMap;
    for (auto &loc : locs) {
        locMap[make_pair(loc.first, loc.second)].first++;
    }
    int total = 0;
    for (auto &loc : locs) {
        if(!locMap[make_pair(loc.second, loc.first)].second && !locMap[make_pair(loc.first, loc.second)].second){
            total += locMap[make_pair(loc.second, loc.first)].first * locMap[make_pair(loc.first, loc.second)].first;
            locMap[make_pair(loc.second, loc.first)].second = locMap[make_pair(loc.first, loc.second)].second=true;
        }
    }
    fout << total << endl;
    return 0;
}