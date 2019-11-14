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
    long long N;
    fin >> N;
    vector<pair<long long, long long>> pairs = vector<pair<long long, long long>>(N);
    // location1, location2
    // location1 < location2
    for (long long i = 0; i < N; i++) {
        fin >> pairs[i].first >> pairs[i].second;
        cout << pairs[i].first << " " << pairs[i].second << endl;
        if (pairs[i].first > pairs[i].second) {
            swap(pairs[i].first, pairs[i].second);
        }
    }
    vector<pair<long long, long long>> criticalPoints;
    // location, slopeChange
    for (long long i = 0; i < N; i++) {
        if (pairs[i].second - pairs[i].first <= min(abs(pairs[i].first), abs(pairs[i].second))) {
            // always shorter to just go directly
            continue;
        }
        if (pairs[i].first == 0) {
            // left side of boundary is at portal
            criticalPoints.push_back(make_pair(0, -1));
            criticalPoints.push_back(make_pair(pairs[i].second, 2));
            criticalPoints.push_back(make_pair(pairs[i].second * 2, -1));
        }
        if (pairs[i].second == 0) {
            // right side of boundary is at portal
            criticalPoints.push_back(make_pair(pairs[i].first * 2, -1));
            criticalPoints.push_back(make_pair(pairs[i].first, 2));
            criticalPoints.push_back(make_pair(0, -1));
        }
        if (pairs[i].first > 0 && pairs[i].second > 0) {
            // both points more than 0
            criticalPoints.push_back(make_pair(pairs[i].first * 2, -1));
            criticalPoints.push_back(make_pair(pairs[i].second, 2));
            criticalPoints.push_back(make_pair(2 * pairs[i].second - 2 * pairs[i].first, -1));
        }
        if (pairs[i].first < 0 && pairs[i].second < 0) {
            // both points less than 0
            criticalPoints.push_back(make_pair(2 * pairs[i].first - 2 * pairs[i].second, -1));
            criticalPoints.push_back(make_pair(pairs[i].second, 2));
            criticalPoints.push_back(make_pair(pairs[i].first * 2, -1));
        }
        if (pairs[i].first < 0 && pairs[i].second > 0) {
            // on both sides of 0
            criticalPoints.push_back(make_pair(2 * pairs[i].first, -1));
            criticalPoints.push_back(make_pair(pairs[i].first, 2));
            criticalPoints.push_back(make_pair(0, -2));
            criticalPoints.push_back(make_pair(pairs[i].second, 2));
            criticalPoints.push_back(make_pair(2 * pairs[i].second, -1));
        }
    }
    sort(criticalPoints.begin(), criticalPoints.end());
    long long currentDist = 0;
    for (long long i = 0; i < N; i++) {
        currentDist += pairs[i].second - pairs[i].first;
    }
    long long minDist = currentDist;
    long long previousLocation = 0;
    long long slope = 0;
    //cout << criticalPoints.size()
    for (long long i = 0; i < criticalPoints.size(); i++) {
        currentDist += (criticalPoints[i].first - previousLocation) * slope;
        previousLocation = criticalPoints[i].first;
        minDist = min(minDist, currentDist);
        cout << currentDist << " @ location " << criticalPoints[i].first << endl;
        slope += criticalPoints[i].second;
    }
    fout << minDist << endl;
    return 0;
}