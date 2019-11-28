// maxcross - Silver - February 2016-2017
// http://usaco.org/index.php?page=viewproblem2&cpid=715

#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("maxcross.in");
    ofstream fout("maxcross.out");
    int N, K, B;
    // number of lights
    // number of minimum consecutive
    // number of broken lights
    fin >> N >> K >> B;
    vector<int> broken = vector<int>(B);
    for (int i = 0; i < B; i++) {
        fin >> broken[i];
    }
    broken.push_back(0);
    broken.push_back(N + 1);
    sort(broken.begin(), broken.end());
    int ans = INFINITY;
    for (auto light = broken.begin(); light != broken.end(); light++) {
        auto lightOutOfRange = lower_bound(broken.begin(), broken.end(), *light + K);
        if (lightOutOfRange != broken.end()) {
            if (*lightOutOfRange - *light > K) {
                ans = min(ans, (int)(lightOutOfRange - light) - 1);
            } else if (*lightOutOfRange - *light == K) {
                ans = min(ans, (int)(lightOutOfRange - light));
            }
        }
    }
    fout << ans << endl;
    return 0;
}