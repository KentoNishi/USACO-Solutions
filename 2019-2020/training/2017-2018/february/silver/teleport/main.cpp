// teleport - Silver - February 2018-2019 - http://usaco.org/index.php?page=viewproblem2&cpid=812

/*
    Summary:

    Solution:

*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ofstream fout("teleport.out");
    ifstream fin("teleport.in");
    int N;
    fin >> N;
    vector<pair<int, int>> pairs = vector<pair<int, int>>(N);
    // location1, location2
    // location1 < location2
    for (int i = 0; i < N; i++) {
        fin >> pairs[i].first >> pairs[i].second;
        if (pairs[i].first > pairs[i].second) {
            swap(pairs[i].first, pairs[i].second);
        }
    }
    vector<pair<int, int>> criticalPoints;
    // location, slopeChange
    for (int i = 0; i < N; i++) {
        if (pairs[i].first == 0) {
            // left side of boundary is at portal
            criticalPoints.push_back(make_pair(pairs[i].first, -1));
            criticalPoints.push_back(make_pair(pairs[i].second, 2));
            criticalPoints.push_back(make_pair(pairs[i].second * 2, -1));
        }
    }
    return 0;
}