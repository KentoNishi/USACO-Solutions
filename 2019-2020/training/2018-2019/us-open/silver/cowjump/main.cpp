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

struct Point {
    long long x, y;
    Point(long long a, long long b){
        x=a;
        y=b;
    }
    Point(){

    }
};

struct Hurdle{
    Point p1;
    Point p2;
    int index;
    int collisions=0;
    Hurdle(Point a, Point b, int i){
        p1=a;
        p2=b;
        index=i;
    }
    Hurdle(){

    }
};

bool isIntersecting(Hurdle h1, Hurdle h2) {
    Point p1=h1.p1;
    Point p2=h1.p2;
    Point q1=h2.p1;
    Point q2=h2.p2;
    return (((q1.x-p1.x)*(p2.y-p1.y) - (q1.y-p1.y)*(p2.x-p1.x))
            * ((q2.x-p1.x)*(p2.y-p1.y) - (q2.y-p1.y)*(p2.x-p1.x)) < 0)
            &&
           (((p1.x-q1.x)*(q2.y-q1.y) - (p1.y-q1.y)*(q2.x-q1.x))
            * ((p2.x-q1.x)*(q2.y-q1.y) - (p2.y-q1.y)*(q2.x-q1.x)) < 0);
}

struct Event{
    int time;
    int index;
    Event(int t, int i){
        time=t;
        index=i;
    }
};

struct SortEvents {
    bool operator()(Event a, Event b) const { 
        return a.time < b.time;
    }
};

vector<Event> timeline;

int main() {
    ofstream fout("cowjump.out");
    ifstream fin("cowjump.in");
    int N;
    fin >> N;
    vector<Hurdle> hurdles;
    // create a list of all hurdles
    for(int i=0;i<N;i++){
        long long a,b,c,d;
        fin >> a >> b >> c >> d;
        hurdles.push_back(Hurdle(Point(a,b),Point(c,d),i));
    }
    // add the events (left point, right point) to a queue
    for(auto &hurdle:hurdles){
        timeline.push_back(Event(min(hurdle.p1.x,hurdle.p2.x),hurdle.index));
        timeline.push_back(Event(max(hurdle.p1.x,hurdle.p2.x),hurdle.index));
    }
    // sort the queue
    sort(timeline.begin(),timeline.end(),SortEvents());
    
    set<Hurdle> activeHurdles;

    for(auto event:timeline){
        
    }

    return 0;
}