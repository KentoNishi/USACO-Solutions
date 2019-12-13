// Test case path: [path]
// div7 - Silver - January 2015-2019
// http://usaco.org/index.php?page=viewproblem2&cpid=595

#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("div7.in");
    ofstream fout("div7.out");
    int N;
    fin >> N;
    vector<int> sumLeft = vector<int>(N + 1, 0);
    for (int i = 0; i < N; i++) {
        fin >> sumLeft[i + 1];
    }
    for (int i = 1; i <= N; i++) {
        sumLeft[i] += sumLeft[i - 1];
        sumLeft[i] %= 7;
    //    cout << sumLeft[i] << " ";
    }
    // cout << endl;
    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (int k = i + 1; k < N; k++) {
            if (((sumLeft[k] - sumLeft[i]) % 7) == 0) {
                ans = max(k - i, ans);
            }
        }
    }
    fout << ans << endl;
    return 0;
}