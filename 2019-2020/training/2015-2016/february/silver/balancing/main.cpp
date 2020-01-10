// Test case path: [path]
// balancing - Division - Month Season
// url

#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("balancing.in");
    ofstream fout("balancing.out");
    vector<pair<int, int>> points;
    int N;
    fin >> N;
    points = vector<pair<int, int>>(N);
    for (int i = 0; i < N; i++) {
        fin >> points[i].first >> points[i].second;
    }
    // sort(points.begin(), points.end());
    //vector<pair<int, int>> pointsByY = points;
    //sort(pointsByY.begin(), pointsByY.end(), [](pair<int, int> a, pair<int, int> b) { return a.second < b.second; });
    int ans = N;
    for (int i = 0; i < N; i++) {
        int dx[] = {-1, -1, 1, 1};
        int dy[] = {-1, 1, -1, 1};
        for (int k = 0; k < 4; k++) {
            int inLeftUp = 0;
            int inRight = 0;
            int inDown = 0;
            int inRightDown = 0;
            int x = points[i].first + dx[k];
            int y = points[i].second + dy[k];
            for (int j = 0; j < N; j++) {
                int nx = points[j].first;
                int ny = points[j].second;
                if (nx > x && ny > y) {
                    inRightDown++;
                }
                if (nx < x && ny > y) {
                    inDown++;
                }
                if (nx > x && ny < y) {
                    inRight++;
                }
                if (nx < x && ny < y) {
                    inLeftUp++;
                }
            }
            // cout << "For " << x << "," << y << " the result is ";
            // cout << inLeftUp << "," << inRight << "," << inDown << "," << inRightDown << endl;
            int localAns = max(max(inLeftUp, inRight), max(inDown, inRightDown));
            // cout << localAns << endl;
            ans = min(ans, localAns);
            // cout << "For " << x << "," << y << " the result is ";
            // cout << inLeftUp << "," << inRight << "," << inDown << "," << inRightDown << endl;
        }
    }
    fout << ans << endl;
    return 0;
}