// Test case path: [path]
// triangles - Division - Month Season
// url

#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("triangles.in");
    ofstream fout("triangles.out");
    int N;
    fin >> N;
    vector<pair<int, int>> points;
    points.resize(N);
    for (int i = 0; i < N; i++) {
        fin >> points[i].first >> points[i].second;
        points[i].first += pow(10, 4);
        points[i].second += pow(10, 4);
    }
    map<int, vector<int>> pointsWithY;
    map<int, vector<int>> pointsWithX;
    for (int i = 0; i < N; i++) {
        pointsWithY[points[i].second].push_back(i);
        pointsWithX[points[i].first].push_back(i);
    }
    int ans = 0;
    for (auto xVals : pointsWithX) {
        // for each X
        int xValue = xVals.first;
        cout << "Trying " << xValue << endl;
        vector<int> pointIDs = xVals.second;
        for (auto pointID : pointIDs) {
            // for each point on that X line
            int yVal = points[pointID].second;
            int totalWidths = 0;
            // add up the widths on that Y line
            for (auto pointYid : pointsWithY[yVal]) {
                totalWidths += abs(points[pointYid].first - xValue);
            }
            int totalHeights = 0;
            for (auto pointXid : xVals.second) {
                totalHeights += abs(points[pointXid].first - yVal);
            }
            cout << "width: " << totalWidths << ", height: " << totalHeights << endl;
            ans += totalHeights * totalWidths;
        }
    }
    fout << ans << endl;
    return 0;
}