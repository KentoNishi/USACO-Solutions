// Test case path: [path]
// angry - Silver - January 2015-2016
// http://usaco.org/index.php?page=viewproblem2&cpid=594

#include <bits/stdc++.h>
using namespace std;
int N, K;
vector<int> blocks;

bool possible(int radius) {
    int diameter = 2 * radius;
    int cowID = 0;
    int blockID = 0;
    int firstInRadius = blocks[0];
    while (cowID < K && blockID < N) {
        if (blocks[blockID] - firstInRadius > diameter) {
            cowID++;
            firstInRadius = blocks[blockID];
            continue;
        }
        blockID++;
    }
    return blockID == N && cowID < K;
}

int main() {
    ifstream fin("angry.in");
    ofstream fout("angry.out");
    fin >> N >> K;
    blocks = vector<int>(N);
    for (int i = 0; i < N; i++) {
        fin >> blocks[i];
    }
    sort(blocks.begin(), blocks.end());
    int right = blocks[N - 1] - blocks[0];
    int left = 0;
    while (right > left && right - left > 1) {
        int test = (right + left) / 2.0;
        if (possible(test)) {
            right = test;
        } else {
            left = test;
        }
    }
    if (possible(left)) {
        fout << left << endl;
    } else {
        fout << right << endl;
    }
    return 0;
}