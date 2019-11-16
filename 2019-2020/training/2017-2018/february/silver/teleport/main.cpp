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
        return;
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
        currentDist += abs(pairs[i].second - pairs[i].first);
    }
    map<long long, long long> map;
    for (long long i = 0; i < N; i++) {
        int a = pairs[i].first;
        int b = pairs[i].second;
        if (abs(a) > abs(a - b)) {
            continue;
        }
        if ((a < b && a < 0) || (a >= b && a >= 0)) {
            addPoint(map, 0, -1);
            addPoint(map, b, 2);
            addPoint(map, 2 * b, -1);
        }
        if ((a < b && a >= 0) || (a >= b && a < 0)) {
            addPoint(map, 2 * a, -1);
            addPoint(map, b, 2);
            addPoint(map, 2 * b - 2 * a, -1);
        }
    }
    long long minDist = currentDist;
    long long previous = 0;
    long long slope = 0;
    for (auto &elem : map) {
        currentDist += slope * (elem.first - previous);
        previous = elem.first;
        slope += elem.second;
        minDist = min(minDist, currentDist);
    }
    fout << minDist << endl;
    return 0;
}