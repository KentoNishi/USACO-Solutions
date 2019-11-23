// pairup - Silver - US-Open 2016-2017
// http://usaco.org/index.php?page=viewproblem2&cpid=738

#include <bits/stdc++.h>
using namespace std;

struct comp {
    bool operator()(pair<int, int> a, pair<int, int> b) const {
        return a.second < b.second;
    }
};

int main() {
    ifstream fin("pairup.in");
    ofstream fout("pairup.out");
    int N, M = 0;
    fin >> N;
    vector<pair<int, int>> counts = vector<pair<int, int>>(N);
    // number, amount
    for (int i = 0; i < N; i++) {
        fin >> counts[i].first >> counts[i].second;
    }
    sort(counts.begin(), counts.end(), comp());
    // sorted by time
    int leftBound = 0;
    int rightBound = N - 1;
    int maxTime = 0;
    while (rightBound >= leftBound) {
        int pairsMade = min(counts[rightBound].first, counts[leftBound].first);
        int timeTaken = counts[rightBound].second + counts[leftBound].second;
        maxTime = max(maxTime, timeTaken);
        counts[rightBound].first -= pairsMade;
        counts[leftBound].first -= pairsMade;
        if (counts[rightBound].first <= 0) {
            rightBound--;
        }
        if (counts[leftBound].first <= 0) {
            leftBound++;
        }
    }
    fout << maxTime << endl;
    return 0;
}