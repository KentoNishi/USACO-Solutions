// Test case path: [path]
// convention2 - Division - Month Season
// url

#include <bits/stdc++.h>
using namespace std;

struct compare {
    bool operator()(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) const {
        return a.second.first < b.second.first;
    }
};

struct qComp {
    bool operator()(pair<int, int> a, pair<int, int> b) const {
        return a.first > b.first;
    }
};

int main() {
    ifstream fin("convention2.in");
    ofstream fout("convention2.out");
    int N;
    fin >> N;
    vector<pair<int, pair<int, int>>> cows = vector<pair<int, pair<int, int>>>(N);
    // <seniority, <arrival, stay>>
    for (int i = 0; i < N; i++) {
        cows[i].first = i;
        fin >> cows[i].second.first >> cows[i].second.second;
    }
    sort(cows.begin(), cows.end(), compare());
    // order of arrival
    priority_queue<pair<int, int>, vector<pair<int, int>>, qComp> queue;
    // seniority, cow id
    queue.push(make_pair(cows[0].first, 0));
    int currentTime = cows[0].second.first;
    int nextCow = 1;
    int ans = 0;
    while (queue.size() > 0) {
        pair<int, int> currentCow = queue.top();
        // cout << "queue size is " << queue.size() << endl;
        queue.pop();
        int arrival = cows[currentCow.second].second.first;
        // cout << "Cow " << "with seniority " << currentCow.first << " labeled " << currentCow.second << " is eating at time " << currentTime << " but it arrived at time " << arrival << endl;
        int stay = cows[currentCow.second].second.second;
        ans = max(ans, currentTime - arrival);
        // cout << "cow arriving next is " << nextCow << endl;
        for (int i = nextCow; i < N; i++) {
            if (cows[i].second.first > currentTime + stay) {
                break;
            }
            // cout << "Cow " << i << " is arriving before time " << currentTime+stay << endl;
            queue.push(make_pair(cows[i].first, i));
            nextCow++;
        }
        currentTime += stay;
        if (nextCow < N && queue.size() == 0) {
            queue.push(make_pair(cows[nextCow].first, nextCow));
        }
    }
    fout << ans << endl;
    return 0;
}