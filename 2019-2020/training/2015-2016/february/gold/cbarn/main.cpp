// Test case path: [path]
// cbarn - Silver - February 2015-2016
// http://usaco.org/index.php?page=viewproblem2&cpid=618

#include <bits/stdc++.h>
using namespace std;

int N;

int main() {
    ifstream fin("cbarn.in");
    ofstream fout("cbarn.out");
    fin >> N;
    vector<int> rooms = vector<int>(N);
    int rightMostEmpty = -1;
    for (int i = 0; i < N; i++) {
        fin >> rooms[i];
        if (rooms[i] == 0) {
            rightMostEmpty = i;
        }
    }
    if (rightMostEmpty == -1) {
        fout << 0 << endl;
        return 0;
    }
    stack<int> recentWaiting;
    int index = rightMostEmpty;
    int ans = 0;
    while (true) {
        for (int i = 0; i < rooms[index]; i++) {
            recentWaiting.emplace(index);
        }
        index++;
        index %= N;
        if (index == rightMostEmpty) {
            break;
        }
    }
    while (true) {
        if (rooms[index] == 0) {
            int closest = recentWaiting.top();
            recentWaiting.pop();
            if (index > closest) {
                ans += pow(index - closest, 2);
            } else {
                ans += pow(N - (closest - index), 2);
            }
            rooms[index]++;
            rooms[closest]--;
        }
        index--;
        if (index == -1) {
            index = N - 1;
        }
        if (index == rightMostEmpty) {
            break;
        }
    }
    fout << ans << endl;
    return 0;
}