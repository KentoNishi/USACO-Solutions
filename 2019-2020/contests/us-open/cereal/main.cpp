// Test case path: [path]
// cereal - Division - Month Season
// http://usaco.org/index.php?page=viewproblem&cpid=1027

#include <bits/stdc++.h>
using namespace std;

int N, M;

vector<vector<int>> stored;
vector<pair<int, int>> choices;

bool doTrace(int cowid, int occupied) {
    if (stored[occupied].size() == 0) {
        stored[occupied].push_back(cowid);
        return true;
    }
    int current = stored[occupied][stored[occupied].size() - 1];
    if (cowid > current) {
        return false;
    }
    stored[occupied].push_back(cowid);
    if (choices[current].first == occupied) {
        return doTrace(current, choices[current].second);
    } else {
        return false;
    }
}

int main() {
    ifstream fin("cereal.in");
    ofstream fout("cereal.out");
    fin >> N >> M;
    choices = vector<pair<int, int>>(N);
    for (int i = 0; i < N; i++) {
        fin >> choices[i].first >> choices[i].second;
        choices[i].first--;
        choices[i].second--;
    }
    stored = vector<vector<int>>(M);
    int total = 0;
    vector<int> ans = vector<int>(N);
    for (int i = N - 1; i >= 0; i--) {
        if (doTrace(i, choices[i].first)) {
            total++;
        }
        ans[i] = total;
    }
    for (int i = 0; i < N; i++) {
        fout << ans[i] << endl;
    }
    return 0;
}