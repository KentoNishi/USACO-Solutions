// Test case path: [path]
// berries - Division - Month Season
// url

#include <bits/stdc++.h>
using namespace std;

void printList(vector<int> buckets) {
    for (int i = 0; i < buckets.size(); i++) {
        cout << buckets[i] << " ";
    }
    cout << endl;
}

int main() {
    ifstream fin("berries.in");
    ofstream fout("berries.out");
    int N, K;
    fin >> N >> K;
    vector<int> trees = vector<int>(N);
    for (int i = 0; i < N; i++) {
        fin >> trees[i];
    }
    int ans = 0;
    sort(trees.begin(), trees.end(), greater<int>());
    for (int i = 2; i <= trees[0]; i++) {
        vector<int> baskets;
        for (int j = 0; j < trees.size(); j++) {
            for (int k = 0; k < trees[j] / i - 1; k++) {
                baskets.push_back(i);
            }
            if (trees[j] >= i) {
                baskets.push_back(i + trees[j] % i);
            }
        }
        sort(baskets.begin(), baskets.end(), greater<int>());
        // printList(baskets);
        if (baskets.size() > K) {
            continue;
        }
        int sum = 0;
        for (int j = K / 2; j < baskets.size(); j++) {
            sum += baskets[j];
        }
        ans = max(ans, sum);
    }
    fout << ans << endl;
    return 0;
}