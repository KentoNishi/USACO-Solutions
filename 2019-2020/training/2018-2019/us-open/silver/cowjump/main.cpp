// cowjump - Silver - US-Open 2018-2019 - http://usaco.org/index.php?page=viewproblem2&cpid=943

/*
    Summary:
        http://usaco.org/current/data/sol_cowjump_silver_open19.html
    Solution:
        http://usaco.org/current/data/sol_cowjump_silver_open19.html
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

double currentTime;

// definition of point
struct Point {
    long long x, y;
    int segmentIndex;
};

// definition of hurdle
struct Hurdle {
    Point p1, p2;
    int index;
};

// vector of hurdles
vector<Hurdle> hurdles;

// comparator for comparing line positions
struct sortPoints {
    bool operator()(Point p1, Point p2) const {
        if (p1.x == p2.x) {
            return p1.y < p2.y;
        }
        return p1.x < p2.x;
    }
};
// start intersection testing code

int sign(long long x) {
    if (x == 0) {
        return 0;
    } else {
        return x < 0 ? -1 : +1;
    }
}

int operator*(Point p1, Point p2) {
    return sign(p1.x * p2.y - p1.y * p2.x);
}

Point operator-(Point p1, Point p2) {
    Point p = {p1.x - p2.x, p1.y - p2.y};
    return p;
}

bool isIntersecting(Hurdle h1, Hurdle h2) {
    Point &p1 = h1.p1, &q1 = h1.p2, &p2 = h2.p1, &q2 = h2.p2;
    return ((q2 - p1) * (q1 - p1)) * ((q1 - p1) * (p2 - p1)) >= 0 && ((q1 - p2) * (q2 - p2)) * ((q2 - p2) * (p1 - p2)) >= 0;
}

// end intersection testing code

// get the value of the hurdle evaluated at currentTime
double eval(Hurdle hurdle) {
    if (hurdle.p1.x == hurdle.p2.x)
        return hurdle.p1.y;
    return hurdle.p1.y + (hurdle.p2.y - hurdle.p1.y) * (currentTime - hurdle.p1.x) / (hurdle.p2.x - hurdle.p1.x);
}

// comparator for sorting hurdles
struct sortActiveHurdles {
    bool operator()(int a, int b) const {
        Hurdle hurdleA = hurdles[a];
        Hurdle hurdleB = hurdles[b];
        if (hurdleA.index == hurdleB.index) {
            return false;
        }
        return eval(hurdleA) < eval(hurdleB);
    }
};

int main() {
    ifstream fin("cowjump.in");
    ofstream fout("cowjump.out");
    int N;
    fin >> N;
    vector<Point> events;
    for (int i = 0; i < N; i++) {
        Hurdle hurdle;
        fin >> hurdle.p1.x >> hurdle.p1.y >> hurdle.p2.x >> hurdle.p2.y;
        hurdle.index = hurdle.p1.segmentIndex = hurdle.p2.segmentIndex = i;
        hurdles.push_back(hurdle);
        events.push_back(hurdle.p1);
        events.push_back(hurdle.p2);
    }
    sort(events.begin(), events.end(), sortPoints());

    // a set of indices of the active hurdles
    set<int, sortActiveHurdles> active;
    int ans1;
    int ans2;
    for(auto event: events){
        currentTime=event.x;
        pair<set<int>::iterator,bool> hurdleStatus=active.insert(event.segmentIndex);
        auto currentHurdle = hurdleStatus.first;
        bool alreadyExisting = !hurdleStatus.second;
        if(alreadyExisting){
            auto hurdleAbove=currentHurdle;
            auto hurdleBelow=currentHurdle;
            hurdleAbove++;
            if(hurdleBelow != active.begin() && hurdleAbove != active.end()){
                hurdleBelow--;
                if(isIntersecting(hurdles[*hurdleAbove],hurdles[*hurdleBelow])){
                    ans1=*hurdleBelow;
                    ans2=*hurdleAbove;
                    break;
                }
            }
            active.erase(currentHurdle);
        }else{
            if(currentHurdle!=active.end()&&next(currentHurdle)!=active.end()){
                auto hurdleAbove=currentHurdle;
                hurdleAbove++;
                if(isIntersecting(hurdles[*currentHurdle],hurdles[*hurdleAbove])){
                    ans1=*currentHurdle;
                    ans2=*hurdleAbove;
                    break;
                }
            }
            if(currentHurdle!=active.begin()){
                auto hurdleBelow=currentHurdle;
                hurdleBelow--;
                if(isIntersecting(hurdles[*currentHurdle],hurdles[*hurdleBelow])){
                    ans1=*currentHurdle;
                    ans2=*hurdleBelow;
                    break;
                }
            }
        }
    }
    cout << ans1 << endl;
    cout << ans2 << endl;
    if(ans1 > ans2){
        swap(ans1, ans2);
    }
    int ans2Intersections=0;
    for(auto hurdle:hurdles){
        if(hurdle.index != ans2 && isIntersecting(hurdles[ans2],hurdle)){
            ans2Intersections++;
        }
    }
    if(ans2Intersections>1){
        fout << ans2 + 1 << endl;
        return 0;
    }
    fout << ans1 + 1 << endl;
    return 0;
}