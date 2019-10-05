// measurement - Silver - December 2017-2018 - http://usaco.org/index.php?page=viewproblem2&cpid=763

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct Event {
    int day;
    int cow;
    int change;
};

struct sortEvents {
    bool operator()(Event a, Event b) const {
        return a.day < b.day;
    }
};

int main() {
    ofstream fout("measurement.out");
    ifstream fin("measurement.in");
    int N, G;
    fin >> N >> G;
    vector<Event> events;
    map<int, int> cowNames;
    int cowID = 0;
    vector<int> topCows;
    for (int i = 0; i < N; i++) {
        Event event = Event();
        int cowName;
        fin >> event.day >> cowName >> event.change;
        if (cowNames.find(cowName) == cowNames.end()) {
            cowNames[cowName] = cowID;
            event.cow = cowID;
            cowID++;
        } else {
            event.cow = cowNames[cowName];
        }
        topCows.push_back(event.cow);
        events.push_back(event);
    }
    vector<int> cows(cowNames.size(), 0);
    sort(events.begin(), events.end(), sortEvents());
    int ans = 0;
    int highest = 0;
    for (auto &event : events) {
        cows[event.cow] += event.change;
        // make the change
        if (cows[event.cow] > highest) {
            // now the highest
            if (topCows.size() != 1 || topCows[0] != event.cow) {
                // if the cow was not already the only top alone
                ans++;
                cout << event.day << " " << event.cow << " " << event.change << endl;
            }
            highest = cows[event.cow];
            topCows = {event.cow};
        } else if (cows[event.cow] == highest) {
            ans++;
            cout << event.day << " " << event.cow << " " << event.change << endl;
        } else {
            // not the highest after change
            auto found = find(topCows.begin(), topCows.end(), event.cow);
            if (found != topCows.end()) {
                // existed in top, but not after change
                topCows.erase(found);
                // remove from highest
                if (topCows.size() == 0) {
                    // if 0 cows are at the top
                    // find a new top cow
                    int localHigh = cows[0];
                    topCows = {0};
                    for (int i = 1; i < cows.size(); i++) {
                        if (cows[i] > localHigh) {
                            localHigh = cows[i];
                            topCows = {i};
                        } else if (cows[i] == localHigh) {
                            topCows.push_back(i);
                        }
                    }
                    // found new top cows
                    highest = localHigh;
                    // set the maximum to the new max
                    if (topCows.size() != 1 || topCows[0] != event.cow) {
                        // if it's not the same cow only
                        ans++;
                        cout << event.day << " " << event.cow << " " << event.change << endl;
                    }
                } else {
                    // more cows still at top
                    ans++;
                    cout << event.day << " " << event.cow << " " << event.change << endl;
                }
            }
        }
    }
    fout << ans << endl;
    return 0;
}