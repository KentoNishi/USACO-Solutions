// Test case path: [path]
// triangles - Silver - February 2019-2020
// http://usaco.org/index.php?page=viewproblem2&cpid=1015

#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x;
    long long y;
    long long width;
    long long height;
};

const long long OFFSET = pow(10, 4);
const long long GRIDSIZE = 2 * OFFSET + 1;
const long long MODULO = 1e9 + 7;
vector<Point> points;

void findSums(vector<vector<long long>> &onAxis, bool axisIsX) {
    for (long long i = 0; i < GRIDSIZE; i++) {
        vector<long long> &arr = onAxis[i];
        if (arr.size() == 0) {
            continue;
        }
        sort(arr.begin(), arr.end(), [&](long long a, long long b) {
            if (axisIsX) {
                return points[a].y < points[b].y;
            } else {
                return points[a].x < points[b].x;
            }
        });
        vector<long long> distSums = vector<long long>(arr.size());
        for (long long j = 1; j < arr.size(); j++) {
            long long dist = abs(points[arr[0]].y - points[arr[j]].y);
            if (!axisIsX) {
                dist = abs(points[arr[0]].x - points[arr[j]].x);
            }
            distSums[0] += dist;
        }
        if (axisIsX) {
            points[arr[0]].height = distSums[0];
        } else {
            points[arr[0]].width = distSums[0];
        }
        for (long long j = 1; j < arr.size(); j++) {
            long long dist = abs(points[arr[j - 1]].y - points[arr[j]].y);
            if (!axisIsX) {
                dist = abs(points[arr[j - 1]].x - points[arr[j]].x);
            }
            distSums[j] = distSums[j - 1] + dist * (2 * j - arr.size());
            if (axisIsX) {
                points[arr[j]].height = distSums[j];
            } else {
                points[arr[j]].width = distSums[j];
            }
        }
    }
}

int main() {
    ifstream fin("triangles.in");
    ofstream fout("triangles.out");
    long long N;
    fin >> N;
    points = vector<Point>(N);
    vector<vector<long long>> withX = vector<vector<long long>>(GRIDSIZE);
    vector<vector<long long>> withY = vector<vector<long long>>(GRIDSIZE);
    for (long long i = 0; i < N; i++) {
        fin >> points[i].x >> points[i].y;
        points[i].x += OFFSET;
        points[i].y += OFFSET;
        withX[points[i].x].push_back(i);
        withY[points[i].y].push_back(i);
    }
    findSums(withX, true);
    findSums(withY, false);
    long long ans = 0;
    for (long long i = 0; i < points.size(); i++) {
        Point p = points[i];
        // cout << "Point at " << p.x - OFFSET << "," << p.y - OFFSET << " has width " << p.width << " and height " << p.height << endl;
        ans += (p.height % MODULO) * (p.width % MODULO);
        ans %= MODULO;
    }
    fout << ans << endl;
    return 0;
}