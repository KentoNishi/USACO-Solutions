// Test case path: [path]
// meetings - Silver - December 2019-2020
// http://usaco.org/index.php?page=viewproblem&cpid=955

#include <bits/stdc++.h>
using namespace std;

struct Cow {
    int position;
    int velocity;
    int weight;
};

int N, L;
vector<Cow> cows;

int getTimeNeeded() {
    vector<int> left, right;
    for (int i = 0; i < N; i++) {
        if (cows[i].velocity == -1) {
            left.push_back(i);
        } else {
            right.push_back(i);
        }
    }
    vector<pair<int, int>> arrivals;
    for (int i = 0; i < left.size(); i++) {
        arrivals.push_back(make_pair(cows[left[i]].position, cows[i].weight));
    }
    for (int i = 0; i < right.size(); i++) {
        arrivals.push_back(make_pair(L - cows[right[i]].position, cows[left.size() + i].weight));
    }
    sort(arrivals.begin(), arrivals.end(), [](pair<int, int> a, pair<int, int> b) {
        return a.first < b.first;
    });
    int totalWeight = 0;
    for (int i = 0; i < N; i++) {
        totalWeight += cows[i].weight;
    }
    for (int i = 0; i < N; i++) {
        totalWeight -= 2 * arrivals[i].second;
        if (totalWeight <= 0) {
            return arrivals[i].first;
        }
    }
}

int main() {
    ifstream fin("meetings.in");
    ofstream fout("meetings.out");
    fin >> N >> L;
    cows = vector<Cow>(N);
    for (int i = 0; i < N; i++) {
        fin >> cows[i].weight >> cows[i].position >> cows[i].velocity;
    }
    sort(cows.begin(), cows.end(), [](Cow a, Cow b) {
        return a.position < b.position;
    });
    int timeNeeded = getTimeNeeded();
    queue<int> right;
    int totalCollisions = 0;
    for (int i = 0; i < N; i++) {
        if (cows[i].velocity == 1) {
            right.push(i);
        } else {
            while (right.size() > 0 && cows[right.front()].position + 2 * timeNeeded < cows[i].position) {
                right.pop();
            }
            totalCollisions += right.size();
        }
    }
    fout << totalCollisions << endl;
    return 0;
}