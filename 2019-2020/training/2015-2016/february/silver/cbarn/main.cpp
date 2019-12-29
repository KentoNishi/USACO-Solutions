// Test case path: [path]
// cbarn - Silver - February 2015-2016
// http://usaco.org/index.php?page=viewproblem2&cpid=618

#include <bits/stdc++.h>
using namespace std;

int N;

vector<priority_queue<int, vector<int>, greater<int>>> rooms;

bool isDone() {
    for (auto &q : rooms) {
        if (q.size() != 1) {
            return false;
        }
    }
    return true;
}

int main() {
    ifstream fin("cbarn.in");
    ofstream fout("cbarn.out");
    fin >> N;
    rooms.resize(N);
    for (int i = 0; i < N; i++) {
        int a;
        fin >> a;
        for (int k = 0; k < a; k++) {
            rooms[i].emplace(0);
        }
    }
    int location = 0;
    while (!isDone()) {
        location = location % N;
        while (rooms[location].size() > 1) {
            rooms[(location + 1) % N].emplace(rooms[location].top() + 1);
            rooms[location].pop();
        }
        location++;
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        ans += pow(rooms[i].top(), 2);
    }
    fout << ans << endl;
    return 0;
}