// Test case path: [path]
// reduce - Silver - US-Open 2015-2016
// http://usaco.org/index.php?page=viewproblem2&cpid=642

#include <bits/stdc++.h>
using namespace std;

int N;
vector<pair<int, int>> points;

struct compareX {
    bool operator()(int a, int b) const {
        return points[a].first < points[b].first;
    }
};

pair<vector<int>, vector<int>> removeFromVectors(vector<int> &v1, vector<int> &v2, int n1, int n2) {
    auto p1 = v1.begin() + n1;
    auto p2 = v2.begin() + n2;
    v1.erase(p1);
    v2.erase(p2);
    return make_pair(v1, v2);
}

struct compareY {
    bool operator()(int a, int b) const {
        return points[a].second < points[b].second;
    }
};

int findArea(vector<int> sortedByX, vector<int> sortedByY, int haveSold) {
    int dx = points[*(--sortedByX.end())].first - points[*(sortedByX.begin())].first;
    int dy = points[*(--sortedByY.end())].second - points[*(sortedByY.begin())].second;
    int area = (dy * dx);
    if (haveSold == 3) {
        return area;
    }
    haveSold++;
    vector<pair<vector<int>::iterator, vector<int>::iterator>> iters = {
        {sortedByX.begin(), find(sortedByY.begin(), sortedByY.end(), *sortedByX.begin())},
        {find(sortedByX.begin(), sortedByX.end(), *sortedByY.begin()), sortedByY.begin()},
        {(--sortedByX.end()), find(sortedByY.begin(), sortedByY.end(), *(--sortedByX.end()))},
        {find(sortedByX.begin(), sortedByX.end(), *(--sortedByY.end())), (--sortedByY.end())},
    };
    for (pair<vector<int>::iterator, vector<int>::iterator> &iter : iters) {
        pair<vector<int>, vector<int>> removed = {sortedByX, sortedByY};
        pair<int, int> dists = {distance(sortedByX.begin(), iter.first), distance(sortedByY.begin(), iter.second)};
        removeFromVectors(removed.first, removed.second, dists.first, dists.second);
        area = min(area, findArea(removed.first, removed.second, haveSold));
    }
    return area;
}

int main() {
    ifstream fin("reduce.in");
    ofstream fout("reduce.out");
    fin >> N;
    points.resize(N);
    vector<int> sortedByX;
    vector<int> sortedByY;
    for (int i = 0; i < N; i++) {
        fin >> points[i].first >> points[i].second;
        sortedByX.push_back(i);
        sortedByY.push_back(i);
    }
    sort(sortedByX.begin(), sortedByX.end(), compareX());
    sort(sortedByY.begin(), sortedByY.end(), compareY());
    fout << findArea(sortedByX, sortedByY, 0) << endl;
    return 0;
}