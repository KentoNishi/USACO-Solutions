// Test case path: [path]
// bcount - Silver - December 2015-2016
// http://usaco.org/index.php?page=viewproblem2&cpid=572

#include <bits/stdc++.h>
using namespace std;

int N, Q;

int main() {
    ifstream fin("bcount.in");
    ofstream fout("bcount.out");
    fin >> N >> Q;
    vector<vector<int>> arrs = vector<vector<int>>(3, vector<int>(N + 1, 0));
    for (int i = 0; i < N; i++) {
        int a;
        fin >> a;
        arrs[a - 1][i + 1]++;
    }
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j < 3; j++) {
            arrs[j][i] += arrs[j][i - 1];
        }
    }
    for (int i = 0; i < Q; i++) {
        int a, b;
        fin >> a >> b;
        a--;
        for (int k = 0; k < 3; k++) {
            fout << arrs[k][b] - arrs[k][a] << (k < 2 ? " " : "");
        }
        fout << endl;
    }
    return 0;
}