// Test case path: [path]
// snowboots - Silver - February 2017-2018
// http://usaco.org/index.php?page=viewproblem2&cpid=811

#include <bits/stdc++.h>
using namespace std;

int N, B;

struct Boot {
    int maxDepth;
    int maxStep;
};

vector<int> tiles;
vector<Boot> boots;
vector<int> dp;

int main() {
    ifstream fin("snowboots.in");
    ofstream fout("snowboots.out");
    fin >> N >> B;
    tiles.resize(N);
    for (int i = 0; i < N; i++) {
        fin >> tiles[i];
    }
    boots.resize(B);
    for (int i = 0; i < B; i++) {
        fin >> boots[i].maxDepth >> boots[i].maxStep;
    }
    dp = vector<int>(N, -1);
    dp[0] = 0;
    for (int i = 0; i < N - 1; i++) {
        int boot = dp[i];
        if (boot == -1) {
            continue;
        }
        while (boot < B) {
            if (boots[boot].maxDepth < tiles[i]) {
                boot++;
                continue;
            }
            for (int j = i + 1; j < N && j <= i + boots[boot].maxStep; j++) {
                if (boots[boot].maxDepth >= tiles[j]) {
                    if (dp[j] == -1) {
                        dp[j] = boot;
                    } else {
                        dp[j] = min(dp[j], boot);
                    }
                }
            }
            boot++;
        }
    }
    fout << dp[N - 1] << endl;
    return 0;
}