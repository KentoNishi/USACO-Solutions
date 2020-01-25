// Test case path: [path]
// berries - Division - Month Season
// url

#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("berries.in");
    ofstream fout("berries.out");
    int N, K;
    fin >> N >> K;
    vector<int> trees = vector<int>(N);
    for (int i = 0; i < N; i++) {
        fin >> trees[i];
    }
    sort(trees.begin(), trees.end(), greater<int>());
    vector<int> baskets = vector<int>(K);
    for (int i = 0; i < K; i++) {
        baskets[i] = trees[i];
    }
    while (baskets[0] / 2 >= baskets[K - 1]) {
        int split = 3;
        while (K - split + 1 > 0 && baskets[0] / split >= baskets[K - split + 1]) {
            split++;
        }
        split--;
        int total = baskets[0];
        while (total >= 2 * baskets[0] / split) {
            baskets.push_back(baskets[0] / split);
            total -= baskets[0] / split;
        }
        baskets.push_back(total);
        baskets.erase(baskets.begin());
        sort(baskets.begin(), baskets.end(), greater<int>());
        while (baskets.size() > K) {
            baskets.erase(baskets.end() - 1);
        }
    }
    int sum = 0;
    for (int i = K / 2; i < K; i++) {
        sum += baskets[i];
    }
    fout << sum << endl;
    return 0;
}