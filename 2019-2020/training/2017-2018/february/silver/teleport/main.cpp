// teleport - Silver - February 2018-2019 - http://usaco.org/index.php?page=viewproblem2&cpid=812

/*
    Summary:

    Solution:

*/

#include <bits/stdc++.h>
using namespace std;

void addPoint(map<long long, long long> &map, long long point, long long num) {

    if (map.count(point) > 0) {
        map[point] += num;
    }
    map[point] = num;
}

int main() {
    ofstream fout("teleport.out");
    ifstream fin("teleport.in");
    long long N;
    fin >> N;
    vector<pair<long long, long long>> pairs = vector<pair<long long, long long>>(N);
    // location1, location2
    // location1 < location2
    long long currentDist = 0;
    for (long long i = 0; i < N; i++) {
        fin >> pairs[i].first >> pairs[i].second;
        cout << pairs[i].first << " " << pairs[i].second << endl;
        if (pairs[i].first > pairs[i].second) {
            swap(pairs[i].first, pairs[i].second);
        }
        currentDist += pairs[i].second - pairs[i].first;
    }
    map<long long, long long> map;
    for (long long i = 0; i < N; i++) {
        if (pairs[i].second - pairs[i].first <= min(abs(pairs[i].first), abs(pairs[i].second))) {
            // if the shortest path is to go directly
            continue;
            // skip this pair
        }
        //    *--|------*
        if (pairs[i].first < 0 && pairs[i].second > 0) {
            // left side less than 0
            // right side more than 0
            addPoint(map, pairs[i].first * 2, -1);
            addPoint(map, pairs[i].first, 2);
            addPoint(map, 0, -2);
            addPoint(map, pairs[i].second, 2);
            addPoint(map, pairs[i].second * 2, -1);
        }
        //     *---*   |
        // |    *---*
        if (pairs[i].second < 0 || pairs[i].first > 0) {
            // both below 0 or both above 0
            addPoint(map, pairs[i].first * 2 - pairs[i].second, -1);
            addPoint(map, pairs[i].first, 2);
            addPoint(map, pairs[i].second, -1);
        }
    }
    vector<pair<int, int>> criticalPoints;
    for (auto &elem : map) {
        criticalPoints.push_back(make_pair(elem.first, elem.second));
    }
    for (long long i = 0; i < criticalPoints.size(); i++) {
        cout << "Point at " << criticalPoints[i].first << " " << criticalPoints[i].second << endl;
    }
    long long minDist = currentDist;
    long long previous = 0;
    long long slope = 0;
    for (long long i = 0; i < criticalPoints.size(); i++) {
        currentDist += slope * (criticalPoints[i].first - previous);
        previous = criticalPoints[i].first;
        slope += criticalPoints[i].second;
        minDist = min(minDist, currentDist);
    }
    fout << minDist << endl;
    return 0;
}