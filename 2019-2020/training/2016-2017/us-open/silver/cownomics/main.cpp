// cownomics - Silver - US-Open 2016-2017
// http://usaco.org/index.php?page=viewproblem2&cpid=739

#include <bits/stdc++.h>
using namespace std;

vector<bool> overlaps = vector<bool>(64);
vector<vector<int>> seqs;
int N, M;

bool possible(int n1, int n2, int n3) {
    bool ok = true;
    for (int i = 0; i < N; i++) {
        overlaps[seqs[i][n1] * 16 + seqs[i][n2] * 4 + seqs[i][n3]] = true;
    }
    for (int i = N; i < 2 * N; i++) {
        if (overlaps[seqs[i][n1] * 16 + seqs[i][n2] * 4 + seqs[i][n3]]) {
            ok = false;
        }
    }
    for (int i = 0; i < N; i++) {
        overlaps[seqs[i][n1] * 16 + seqs[i][n2] * 4 + seqs[i][n3]] = false;
    }
    return ok;
}

int toNum(char s) {
    if (s == 'A') {
        return 0;
    }
    if (s == 'T') {
        return 1;
    }
    if (s == 'G') {
        return 2;
    }
    return 3;
}

int main() {
    ifstream fin("cownomics.in");
    ofstream fout("cownomics.out");
    fin >> N >> M;
    seqs = vector<vector<int>>(N * 2, vector<int>(M));
    for (int i = 0; i < 2 * N; i++) {
        string s;
        fin >> s;
        for (int k = 0; k < s.size(); k++) {
            seqs[i][k] = toNum(s[k]);
        }
    }
    int ans = 0;
    for (int n1 = 0; n1 < M; n1++) {
        for (int n2 = n1 + 1; n2 < M; n2++) {
            for (int n3 = n2 + 1; n3 < M; n3++) {
                if (possible(n1, n2, n3)) {
                    ans++;
                }
            }
        }
    }
    fout << ans << endl;
    return 0;
}