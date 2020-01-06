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
    {
        // remove smallest X
        vector<int> byX = sortedByX;
        vector<int> byY = sortedByY;
        auto ptr = byX.begin();
        int val = *ptr;
        byX.erase(ptr);
        byY.erase(find(byY.begin(), byY.end(), val));
        area = min(area, findArea(byX, byY, haveSold));
    }
    {
        // remove smallest Y
        vector<int> byX = sortedByX;
        vector<int> byY = sortedByY;
        auto ptr = byY.begin();
        int val = *ptr;
        byX.erase(find(byX.begin(), byX.end(), val));
        byY.erase(ptr);
        area = min(area, findArea(byX, byY, haveSold));
    }
    {
        // remove largest X
        vector<int> byX = sortedByX;
        vector<int> byY = sortedByY;
        auto ptr = (--byX.end());
        int val = *ptr;
        byX.erase(ptr);
        byY.erase(find(byY.begin(), byY.end(), val));
        area = min(area, findArea(byX, byY, haveSold));
    }
    {
        // remove largest Y
        vector<int> byX = sortedByX;
        vector<int> byY = sortedByY;
        auto ptr = (--byY.end());
        int val = *ptr;
        byX.erase(find(byX.begin(), byX.end(), val));
        byY.erase(ptr);
        area = min(area, findArea(byX, byY, haveSold));
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