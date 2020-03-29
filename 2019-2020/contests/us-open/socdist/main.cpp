// Test case path: [path]
// socdist - Division - Month Season
// http://usaco.org/index.php?page=viewproblem&cpid=1026

#include <bits/stdc++.h>
using namespace std;

int N, M;

vector<pair<int, int>> grass;

bool ok(int num) {
    int lastCow = -num;
    int numCows = 0;
    for (int i = 0; i < M; i++) {
        int right = grass[i].second;
        int left = grass[i].first;
        left = max(left, lastCow + num);
        if (left > right) {
            continue;
        }
        if (left == right) {
            numCows++;
            lastCow = left;
            continue;
        }
        int cowsInRange = 1 + (right - left) / num;
        lastCow = left + num * (cowsInRange - 1);
        numCows += cowsInRange;
        if (numCows >= N) {
            return true;
        }
    }
    if (numCows >= N) {
        return true;
    }
    return false;
}

int main() {
    ifstream fin("socdist.in");
    ofstream fout("socdist.out");
    fin >> N >> M;
    grass = vector<pair<int, int>>(M);
    for (int i = 0; i < M; i++) {
        fin >> grass[i].first >> grass[i].second;
    }
    sort(grass.begin(), grass.end());
    int low = 1;
    int high = grass[M - 1].second - grass[0].first;
    while (high > low + 1) {
        int mid = (high + low) / 2;
        if (ok(mid)) {
            low = mid;
        } else {
            high = mid;
        }
    }
    if (ok(high)) {
        fout << high << endl;
    } else {
        fout << low << endl;
    }
    return 0;
}