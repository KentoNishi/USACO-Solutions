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

double currentTime = 0;

struct Point {
    long long x, y;
    Point(long long a, long long b) {
        x = a;
        y = b;
    }
    Point() {
    }
};

struct Hurdle {
    Point p1;
    Point p2;
    int index;
    int collisions = 0;
    Hurdle(Point a, Point b, int i) {
        p1 = a;
        p2 = b;
        index = i;
    }
    Hurdle() {
    }
};

bool isIntersecting(Hurdle h1, Hurdle h2) {
    cout << h1.index << " " << h2.index << endl;
    Point p1 = h1.p1;
    Point p2 = h1.p2;
    Point q1 = h2.p1;
    Point q2 = h2.p2;
    return (((q1.x - p1.x) * (p2.y - p1.y) - (q1.y - p1.y) * (p2.x - p1.x)) * ((q2.x - p1.x) * (p2.y - p1.y) - (q2.y - p1.y) * (p2.x - p1.x)) < 0) &&
           (((p1.x - q1.x) * (q2.y - q1.y) - (p1.y - q1.y) * (q2.x - q1.x)) * ((p2.x - q1.x) * (q2.y - q1.y) - (p2.y - q1.y) * (q2.x - q1.x)) < 0);
}

struct Event {
    int time;
    int index;
    Event(int t, int i) {
        time = t;
        index = i;
    }
};

struct SortEvents {
    bool operator()(Event a, Event b) const {
        return a.time < b.time;
    }
};

double linePosition(Hurdle hurdle) {
    if (hurdle.p1.x == hurdle.p2.x) {
        return hurdle.p1.y;
    }
    // y intercept + (change in y / change in x)*distance of x
    return hurdle.p1.y + 
        (double)(currentTime - hurdle.p1.x) *
        (double)(hurdle.p2.y - hurdle.p1.y) /
        (double)(hurdle.p2.x - hurdle.p1.y);
}

vector<Hurdle> hurdles;
struct sortActiveHurdles {
    bool operator()(int aIndex, int bIndex) const {
        Hurdle a=hurdles[aIndex];
        Hurdle b=hurdles[bIndex];
        if (a.index == b.index) {
            return false;
        }
        return linePosition(a) < linePosition(b);
    }
};

vector<Event> timeline;

int main() {
    ofstream fout("cowjump.out");
    ifstream fin("cowjump.in");
    int N;
    fin >> N;
    // create a list of all hurdles
    for (int i = 0; i < N; i++) {
        long long a, b, c, d;
        fin >> a >> b >> c >> d;
        hurdles.push_back(Hurdle(Point(a, b), Point(c, d), i));
    }
    // add the events (left point, right point) to a queue
    for (auto &hurdle : hurdles) {
        timeline.push_back(Event(min(hurdle.p1.x, hurdle.p2.x), hurdle.index));
        timeline.push_back(Event(max(hurdle.p1.x, hurdle.p2.x), hurdle.index));
    }
    // sort the queues
    sort(timeline.begin(), timeline.end(), SortEvents());

    set<int, sortActiveHurdles> activeHurdles;
    int ans1;
    int ans2;

    for (auto event : timeline) {
        currentTime = event.time;
        pair<set<int>::iterator, bool> hurdleStatus = activeHurdles.insert(event.index);
        set<int>::iterator currentHurdle = hurdleStatus.first;
        if (hurdleStatus.second == false) {
            // element already exists in the set
            if (currentHurdle != activeHurdles.begin() && currentHurdle != activeHurdles.end()) {
                // if the line is not at the top or bottom
                // check intersections of the line above and below
                // as if the line doesn't exist
                set<int>::iterator hurdleAbove = currentHurdle;
                hurdleAbove++;
                set<int>::iterator hurdleBelow = currentHurdle;
                hurdleBelow--;
                if (isIntersecting(hurdles[*hurdleAbove], hurdles[*hurdleBelow])) {
                    ans1 = *hurdleAbove;
                    ans2 = *hurdleBelow;
                    break;
                }
            }
            activeHurdles.erase(currentHurdle);
        } else {
            // element was just inserted
            // check the instersections of the new line
            // with the line above and below
            set<int>::iterator hurdleAbove = currentHurdle;
            set<int>::iterator hurdleBelow = currentHurdle;
            if (currentHurdle != activeHurdles.end() && next(currentHurdle) != activeHurdles.end()) {
                hurdleAbove++;
                if (isIntersecting(hurdles[*hurdleAbove], hurdles[*currentHurdle])) {
                    ans1 = hurdles[*currentHurdle].index;
                    ans2 = hurdles[*hurdleAbove].index;
                    break;
                }
            }
            if (currentHurdle != activeHurdles.begin()) {
                hurdleBelow--;
                if (isIntersecting(hurdles[*hurdleBelow], hurdles[*currentHurdle])) {
                    ans1 = hurdles[*currentHurdle].index;
                    ans2 = hurdles[*hurdleBelow].index;
                    break;
                }
            }
        }
    }
    if(ans1>ans2){
        swap(ans1,ans2);
        // ans2 always has the bigger index
    }
    int ans2Intersections=0;
    for(auto hurdle: hurdles){
        if(hurdle.index != ans2 && isIntersecting(hurdle, hurdles[ans2])){
            ans2Intersections++;
        }
    }
    if(ans2Intersections > 1){
        // the larger index line has more than one intersection
        fout << ans2 + 1 << endl;
        return 0;
    }
    // if ans2 has less than or equal to one intersections,
    // the smaller index line must be the answer.
    fout << ans1 + 1 << endl;

    return 0;
}