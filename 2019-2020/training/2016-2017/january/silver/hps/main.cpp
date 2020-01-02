// Test case path: [path]
// hps - Silver - January 2016-2017
// http://usaco.org/index.php?page=viewproblem2&cpid=691

#include <bits/stdc++.h>
using namespace std;

int N;

int main() {
    ifstream fin("hps.in");
    ofstream fout("hps.out");
    fin >> N;
    vector<int> moves = vector<int>(N);
    for (int i = 0; i < N; i++) {
        char a;
        fin >> a;
        int b;
        if (a == 'H') {
            b = 0;
        } else if (a == 'P') {
            b = 1;
        } else {
            b = 2;
        }
        moves[i] = b;
    }
    vector<vector<int>> toLeft = vector<vector<int>>(3, vector<int>(N + 1, 0));
    vector<vector<int>> toRight = toLeft;
    for (int i = 0; i < N; i++) {
        toLeft[moves[i]][i + 1]++;
        toRight[moves[i]][i]++;
    }
    for (int i = 1; i < N + 1; i++) {
        for (int k = 0; k < 3; k++) {
            toLeft[k][i] += toLeft[k][i - 1];
        }
    }
    for (int i = N - 1; i >= 0; i--) {
        for (int k = 0; k < 3; k++) {
            toRight[k][i] += toRight[k][i + 1];
        }
    }
    /*
    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < N + 1; i++) {
            cout << toLeft[k][i] << " ";
        }
        cout << endl;
    }
    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < N + 1; i++) {
            cout << toRight[k][i] << " ";
        }
        cout << endl;
    }
    */
    int ans = 0;
    for (int i = 0; i < N + 1; i++) {
        for (int k = 0; k < 3; k++) {
            for (int j = 0; j < 3; j++) {
                ans = max(ans, toLeft[k][i] + toRight[j][i]);
            }
        }
    }
    fout << ans << endl;
    return 0;
}