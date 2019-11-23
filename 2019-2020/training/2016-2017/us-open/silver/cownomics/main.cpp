// cownomics - Silver - US-Open 2016-2017
// http://usaco.org/index.php?page=viewproblem2&cpid=739

#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("cownomics.in");
    ofstream fout("cownomics.out");
    int N, M;
    fin >> N >> M;
    vector<vector<char>> seqs = vector<vector<char>>(N * 2, vector<char>(M));
    for (int i = 0; i < 2 * N; i++) {
        string s;
        fin >> s;
        for (int k = 0; k < s.size(); k++) {
            seqs[i][k] = s[k];
        }
    }
    vector<pair<map<char, int>, bool>> signs = vector<pair<map<char, int>, bool>>(M);
    // <character status, comfirmed to be bad>
    for (int k = 0; k < M; k++) {
        if (signs[k].second) {
            continue;
        }
        for (int i = 0; i < 2 * N; i++) {
            int spotty = (i < N) ? 1 : 2;
            char &c = seqs[i][k];
            if (signs[k].first.find(c) != signs[k].first.end() && signs[k].first[c] != spotty) {
                signs[k].second = true;
                break;
            } else {
                signs[k].first[c] = spotty;
            }
        }
    }
    for (auto &p : signs) {
        cout << "Location is " << (p.second ? "bad" : "good") << endl;
    }
    int ans = 0;
    for (int j1 = 0; j1 < M; j1++) {
        for (int j2 = j1 + 1; j2 < M; j2++) {
            for (int j3 = j2 + 1; j3 < M; j3++) {
                if (!(signs[j3].second && signs[j2].second && signs[j1].second)) {
                    cout << j1 << " " << j2 << " " << j3 << " is good " << endl;
                    ans++;
                }
            }
        }
    }
    fout << ans << endl;
    return 0;
}