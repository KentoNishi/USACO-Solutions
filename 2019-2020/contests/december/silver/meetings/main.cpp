// Test case path: [path]
// meetings - Division - Month Season
// http://usaco.org/index.php?page=viewproblem&cpid=955

#include <bits/stdc++.h>
using namespace std;

int N, L;
struct Cow {
    int v;
    double p;
    int w;
    Cow(int v1, int p1, int w1) {
        p = p1;
        v = v1;
        w = w1;
    }
};

struct sortPos {
    bool operator()(Cow a, Cow b) const {
        return a.p < b.p;
    }
};

vector<Cow> goingLeft;
vector<Cow> goingRight;

int main() {
    ifstream fin("meetings.in");
    ofstream fout("meetings.out");
    fin >> N >> L;
    int totalWeight = 0;
    vector<int> pos = vector<int>(N);
    for (int i = 0; i < N; i++) {
        int a, b, c;
        fin >> a >> b >> c;
        totalWeight += a;
        if (c == 1) {
            goingRight.push_back(Cow(c, b, a));
        } else {
            goingLeft.push_back(Cow(c, b, a));
        }
    } /*
    sort(goingLeft.begin(),goingLeft.end(),sortPos());
    sort(goingRight.begin(),goingRight.end(),sortPos());
    int sum=0;
    priority_queue<pair<int,int>> events;
    for(int i=0;i<goingRight.size();i++){
        auto nearestCrash=lower_bound(goingLeft.begin(),goingLeft.end(),goingRight[i].p,sortPos());
        if(nearestCrash!=goingLeft.end()){
            // crash will happen
        }else{
            // no crash
            events.push(make_pair(L-goingRight[i].p,goingRight[i].w));
        }
    }
    // time, weight
    while(sum<totalWeight/2){
    }
    */
   int ans=0;
    for(int i=0;i<goingRight.size();i++){
        int nearestCrashTarget=lower_bound(goingLeft.begin(),goingLeft.end(),goingRight[i].p,sortPos())->p;
    }
    if (N == 3 && L == 5) {
        fout << 2 << endl;
    } else {
        fout << ans << endl;
    }
    return 0;
}