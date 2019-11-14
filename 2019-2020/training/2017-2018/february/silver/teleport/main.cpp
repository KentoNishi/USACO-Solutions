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
            criticalPoints.push_back(make_pair(0, -1));
            criticalPoints.push_back(make_pair(pairs[i].second, 2));
            criticalPoints.push_back(make_pair(pairs[i].second * 2, -1));
        }
        if (pairs[i].second == 0) {
            // right side of boundary is at portal
            criticalPoints.push_back(make_pair(pairs[i].first*2, -1));
            criticalPoints.push_back(make_pair(pairs[i].first, 2));
            criticalPoints.push_back(make_pair(0, -1));
        }
        if(pairs[i].second-pairs[i].first<=min(abs(pairs[i].first),abs(pairs[i].second))){
            // always shorter to just go directly
            continue;
        }
        if(pairs[i].first>0 && pairs[i].second>0){
            // both points more than 0
            criticalPoints.push_back(make_pair(pairs[i].first*2, -1));
            criticalPoints.push_back(make_pair(pairs[i].second, 2));
            criticalPoints.push_back(make_pair(2*pairs[i].second-2*pairs[i].first, -1));
        }
        if(pairs[i].first<0 && pairs[i].second<0){
            // both points less than 0
            criticalPoints.push_back(make_pair(2*pairs[i].first-2*pairs[i].second, -1));
            criticalPoints.push_back(make_pair(pairs[i].second, 2));
            criticalPoints.push_back(make_pair(pairs[i].first*2, -1));
        }
    }
    return 0;
}