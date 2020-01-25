// Test case path: [path]
// berries - Silver - January 2019-2020
// http://usaco.org/index.php?page=viewproblem2&cpid=990

#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("berries.in");
    ofstream fout("berries.out");
    int N, K;
    fin >> N >> K;
    vector<int> trees = vector<int>(N);
    int maxInBasket = 0;
    for (int i = 0; i < N; i++) {
        fin >> trees[i];
        maxInBasket = max(maxInBasket, trees[i]);
    }
    int ans = 0;
    for (int capacity = 1; capacity <= maxInBasket; capacity++) {
        int basketsOfCapacity = 0;
        for (int i = 0; i < N; i++) {
            basketsOfCapacity += trees[i] / capacity;
        }
        if (basketsOfCapacity < K / 2) {
            break;
        }
        if (basketsOfCapacity >= K) {
            ans = max(ans, capacity * K / 2);
            continue;
        }
        vector<int> berriesLeft = trees;
        for (auto &item : berriesLeft) {
            item = item % capacity;
        }
        sort(berriesLeft.begin(), berriesLeft.end(), greater<int>());
        int sum = capacity * (basketsOfCapacity - K / 2);
        for (int i = 0; i < N && i + basketsOfCapacity < K; i++) {
            sum += berriesLeft[i];
        }
        ans = max(ans, sum);
    }
    fout << ans << endl;
    return 0;
}