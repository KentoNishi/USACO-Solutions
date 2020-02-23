// Test case path: [path]
// swap - Division - Month Season
// url

#include <bits/stdc++.h>
using namespace std;

int N, M, K;

void trace(vector<int> &ans, vector<int> &mapTo, int index) {
    vector<int> chain = {index};
    int current = mapTo[index];
    while (current != index) {
        chain.push_back(current);
        current = mapTo[current];
    }
    // cout << "Chain when starting at " << index + 1 << endl;
    for (int i = 0; i < chain.size(); i++) {
        // cout << chain[i] << endl;
        int endPos = chain[i];
        int startIndex = i - K;
        if (startIndex < 0) {
            startIndex = (chain.size() - ((-startIndex) % chain.size())) % chain.size();
        }
        ans[endPos] = chain[startIndex];
    }
}

int main() {
    ifstream fin("swap.in");
    ofstream fout("swap.out");
    fin >> N >> M >> K;
    vector<pair<int, int>> swaps;
    swaps.resize(M);
    for (int i = 0; i < M; i++) {
        fin >> swaps[i].first >> swaps[i].second;
        swaps[i].first--;
        swaps[i].second--;
    }
    vector<int> locs = vector<int>(N);
    for (int i = 0; i < N; i++) {
        locs[i] = i;
    }
    for (int i = 0; i < swaps.size(); i++) {
        int p1 = swaps[i].first;
        int p2 = swaps[i].second;
        reverse(locs.begin() + p1, locs.begin() + p2 + 1);
    }
    vector<int> mapTo = vector<int>(N);
    for (int i = 0; i < N; i++) {
        mapTo[locs[i]] = i;
    }
    vector<int> ans = vector<int>(N, -1);
    for (int i = 0; i < N; i++) {
        if (ans[i] == -1) {
            trace(ans, mapTo, i);
        }
        fout << ans[i] + 1 << endl;
    }
    return 0;
}