// Test case path: [path]
// cowdance - Silver - January 2016-2017
// http://usaco.org/index.php?page=viewproblem2&cpid=690

#include <bits/stdc++.h>
using namespace std;

int N, Tmax;

vector<int> cows;

int test(int K) {
    priority_queue<int, vector<int>, greater<int>> stage;
    // time of exit
    for (int i = 0; i < K; i++) {
        stage.emplace(cows[i]);
    }
    int currentTime = 0;
    int currentCow = K;
    while (stage.size() > 0) {
        currentTime = stage.top();
        stage.pop();
        if (currentCow < N) {
            stage.emplace(cows[currentCow] + currentTime);
            currentCow++;
        }
    }
    return currentTime;
}

int main() {
    ifstream fin("cowdance.in");
    ofstream fout("cowdance.out");
    fin >> N >> Tmax;
    cows.resize(N);
    for (int i = 0; i < N; i++) {
        fin >> cows[i];
    }
    int leftBound = 1;
    int rightBound = N;
    while (leftBound < rightBound - 1) {
        // cout << leftBound << "," << rightBound << endl;
        int average = (leftBound + rightBound) / 2;
        if (test(average) <= Tmax) {
            rightBound = average;
        } else {
            leftBound = average;
        }
    }
    int left = test(leftBound);
    if (left <= Tmax) {
        fout << leftBound << endl;
    } else {
        fout << rightBound << endl;
    }
    return 0;
}