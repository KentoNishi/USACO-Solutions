// Test case path: [path]
// convention - Silver - December 2018-2019
// http://usaco.org/index.php?page=viewproblem2&cpid=858

#include <bits/stdc++.h>
using namespace std;

int N, M, C;
vector<int> cows;

bool possible(int maxWait) {
    vector<vector<int>> buses = vector<vector<int>>(M);
    int currentBus = 0;
    int cow = 0;
    while (currentBus < M && cow < cows.size()) {
        if (buses[currentBus].size() == C || (buses[currentBus].size() > 0 && cows[cow] - buses[currentBus][0] > maxWait)) {
            currentBus++;
            continue;
        }
        if (buses[currentBus].size() == 0 || cows[cow] - buses[currentBus][0] <= maxWait) {
            buses[currentBus].push_back(cows[cow]);
            cow++;
        }
    }
    return cow == cows.size();
}

int main() {
    ifstream fin("convention.in");
    ofstream fout("convention.out");
    fin >> N >> M >> C;
    // N: The number of cows
    // M: Number of buses
    // C: Number of seats in each bus
    cows = vector<int>(N);
    for (int i = 0; i < N; i++) {
        fin >> cows[i];
    }
    sort(cows.begin(), cows.end());
    int right = cows[N - 1];
    int left = 0;
    while (right > left && right - left > 1) {
        int test = (right + left) / 2.0;
        if (possible(test)) {
            right = test;
        } else {
            left = test;
        }
    }
    if (possible(left)) {
        fout << left << endl;
    } else {
        fout << right << endl;
    }
    return 0;
}