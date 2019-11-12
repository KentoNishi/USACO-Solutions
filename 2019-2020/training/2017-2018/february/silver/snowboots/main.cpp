// reststops - Silver - February 2017-2018 - http://usaco.org/index.php?page=viewproblem2&cpid=811

/*
    Summary:

    Solution:

*/

#include <bits/stdc++.h>
using namespace std;

struct Boot {
    int maxHeight;
    int maxLength;
    Boot() {
        maxHeight = 69;
        maxLength = 69;
    }
};

vector<Boot> boots;
vector<int> tiles;
vector<vector<bool>> visited;
int N, B;
int ans = -1;

void minBoots(int tile, int boot) {
    // currentTile, currentBoot
    if (visited[tile][boot]) {
        return;
    }
    visited[tile][boot] = true;
    if (tile == N - 1) {
        if (ans == -1) {
            ans = boot;
        } else {
            ans = min(ans, boot);
        }
        return;
    }
    cout << N << " " << tile << " " << boots[boot].maxLength << endl;
    for (int nextTile = tile + 1; nextTile < N && nextTile - tile <= boots[boot].maxLength; nextTile++) {
        if (boots[boot].maxHeight >= tiles[nextTile]) {
            minBoots(nextTile, boot);
        }
    }
    for (int nextBoot = boot + 1; nextBoot < B; nextBoot++) {
        if (boots[nextBoot].maxHeight >= tiles[tile]) {
            minBoots(tile, nextBoot);
        }
    }
}

int main() {
    ofstream fout("snowboots.out");
    ifstream fin("snowboots.in");
    fin >> N >> B;
    tiles = vector<int>(N);
    visited = vector<vector<bool>>(N, vector<bool>(B, false));
    for (int i = 0; i < N; i++) {
        fin >> tiles[i];
    }
    boots = vector<Boot>(B);
    for (int i = 0; i < B; i++) {
        boots[i] = Boot();
        fin >> boots[i].maxHeight >> boots[i].maxLength;
    }
    minBoots(0, 0);
    fout << ans << endl;
    return 0;
}