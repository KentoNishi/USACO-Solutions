// Test case path: [path]
// triangles - Silver - February 2019-2020
// url

#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("triangles.in");
    ofstream fout("triangles.out");
    long long N;
    fin >> N;
    vector<pair<long long, long long>> points;
    points.resize(N);
    for (long long i = 0; i < N; i++) {
        fin >> points[i].first >> points[i].second;
        points[i].first += pow(10, 4);
        points[i].second += pow(10, 4);
    }
    unordered_map<long long, vector<long long>> pointsWithX;
    unordered_map<long long, vector<long long>> pointsWithY;
    for (long long i = 0; i < N; i++) {
        pointsWithY[points[i].second].push_back(i);
        pointsWithX[points[i].first].push_back(i);
    }
    long long ans = 0;
    // for each x value
    for (auto it1 : pointsWithX) {
        long long xValue = it1.first;
        vector<long long> &pointsOnX = it1.second;
        if (pointsOnX.size() == 1) {
            continue;
        }
        // for each point in that x axis
        for (auto it2 : pointsOnX) {
            pair<long long, long long> thePoint = points[it2];
            // for each point with the same y value as thePoint
            long long width = 0;
            long long height = 0;
            if (pointsWithY[thePoint.second].size() == 1) {
                goto theEnd;
            }
            for (auto it3 : pointsWithY[thePoint.second]) {
                pair<long long, long long> thePoint2 = points[it3];
                // add the difference in x to the widths
                width += abs(thePoint2.first - thePoint.first);
                width %= 1000000007;
            }
            for (auto it3 : pointsOnX) {
                pair<long long, long long> thePoint2 = points[it3];
                // add the difference in y to the heights
                height += abs(thePoint2.second - thePoint.second);
                height %= 1000000007;
            }
            ans += height * width;
            ans %= 1000000007;
        theEnd:
            continue;
        }
    }
    fout << ans << endl;
    return 0;
}