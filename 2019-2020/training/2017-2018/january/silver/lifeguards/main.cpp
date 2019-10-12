// lifeguards - Silver - January 2017-2018 - http://usaco.org/index.php?page=viewproblem2&cpid=786

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct Event {
    int id;
    int time;
    Event(int i, int t) {
        id = i;
        time = t;
    }
};

struct sortEvents {
    bool operator()(Event a, Event b) const {
        return a.time < b.time;
    }
};

int main() {
    ofstream fout("lifeguards.out");
    ifstream fin("lifeguards.in");
    int N;
    fin >> N;
    vector<int> lifeguards(N, 0);
    vector<Event> events;
    for (int i = 0; i < N; i++) {
        int a, b;
        fin >> a >> b;
        events.push_back(Event(i, a));
        events.push_back(Event(i, b));
    }
    sort(events.begin(), events.end(), sortEvents());
    set<int> current;
    int time = 0;
    int totalTime = 0;
    for (auto &event : events) {
        if (current.size() == 1) {
            // cow is alone
            lifeguards[*current.begin()] = event.time - time;
        }
        if (current.size() > 0) {
            totalTime += event.time - time;
        }
        if (current.find(event.id) != current.end()) {
            // currently existed, end of shift
            current.erase(event.id);
        } else {
            // new cow
            current.insert(event.id);
        }
        time = event.time;
    }
    int minAlone = lifeguards[0];
    for (auto &cow : lifeguards) {
        minAlone = min(minAlone, cow);
    }
    fout << totalTime - minAlone << endl;
    return 0;
}