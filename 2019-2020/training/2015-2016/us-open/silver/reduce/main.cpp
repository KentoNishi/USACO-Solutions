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

int findArea(multiset<int, compareX> sortedByX, multiset<int, compareY> sortedByY, int haveSold) {
    // cout << sortedByX.size() << "," << sortedByY.size() << endl;
    int dx = points[*(--sortedByX.end())].first - points[*(sortedByX.begin())].first;
    int dy = points[*(--sortedByY.end())].second - points[*(sortedByY.begin())].second;
    int area = (dy * dx);
    if (haveSold == 3) {
        return area;
    }
    haveSold++;
    {
        // remove smallest X
        multiset<int, compareX> byX = sortedByX;
        multiset<int, compareY> byY = sortedByY;
        auto ptr = byX.begin();
        byX.erase(ptr);
        byY.erase(byY.find(*ptr));
        area = min(area, findArea(byX, byY, haveSold));
    }
    {
        // remove smallest Y
        multiset<int, compareX> byX = sortedByX;
        multiset<int, compareY> byY = sortedByY;
        auto ptr = byY.begin();
        byX.erase(byX.find(*ptr));
        byY.erase(ptr);
        area = min(area, findArea(byX, byY, haveSold));
    }
    {
        // remove largest X
        multiset<int, compareX> byX = sortedByX;
        multiset<int, compareY> byY = sortedByY;
        auto ptr = (--byX.end());
        byX.erase(ptr);
        byY.erase(byY.find(*ptr));
        area = min(area, findArea(byX, byY, haveSold));
    }
    {
        // remove largest Y
        multiset<int, compareX> byX = sortedByX;
        multiset<int, compareY> byY = sortedByY;
        auto ptr = (--byY.end());
        byX.erase(byX.find(*ptr));
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
    multiset<int, compareX> sortedByX;
    multiset<int, compareY> sortedByY;
    for (int i = 0; i < N; i++) {
        fin >> points[i].first >> points[i].second;
        sortedByX.insert(i);
        sortedByY.insert(i);
    }
    fout << findArea(sortedByX, sortedByY, 0) << endl;
    return 0;
}