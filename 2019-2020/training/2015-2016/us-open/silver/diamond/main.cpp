// Test case path: [path]
// diamond - Silver - US-Open 2015-2016
// http://usaco.org/index.php?page=viewproblem2&cpid=643

#include <bits/stdc++.h>
using namespace std;

int N, K;
vector<int> nums;

int main() {
    ifstream fin("diamond.in");
    ofstream fout("diamond.out");
    fin >> N >> K;
    nums.resize(N);
    for (int i = 0; i < N; i++) {
        fin >> nums[i];
    }
    sort(nums.begin(), nums.end());
    vector<int> largestGroupToLeft = vector<int>(N + 1, 1);
    vector<int> largestGroupToRight = vector<int>(N + 1, 1);
    vector<int> sizes = vector<int>(N);
    largestGroupToLeft[0] = 0;
    largestGroupToRight[N] = 0;
    int rightBound = 1;
    for (int leftBound; rightBound <= N && leftBound < N; leftBound++) {
        while (rightBound < N && nums[rightBound] - nums[leftBound] <= K) {
            rightBound++;
        }
        int size = rightBound - leftBound;
        largestGroupToLeft[rightBound] = max(largestGroupToLeft[rightBound], size);
        largestGroupToRight[leftBound] = max(largestGroupToRight[leftBound], size);
        sizes[leftBound] = size;
    }
    for (int i = 1; i <= N; i++) {
        largestGroupToLeft[i] = max(largestGroupToLeft[i], largestGroupToLeft[i - 1]);
    }
    for (int i = N - 1; i >= 0; i--) {
        largestGroupToRight[i] = max(largestGroupToRight[i], largestGroupToRight[i + 1]);
    }
    /*
    for (int i = 0; i <= N; i++) {
        cout << largestGroupToLeft[i] << " ";
    }
    cout << endl;
    for (int i = 0; i <= N; i++) {
        cout << largestGroupToRight[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < N; i++) {
        cout << sizes[i] << " ";
    }
    cout << endl;
    */
    int ans = 2;
    for (int i = 0; i < N; i++) {
        int sum = sizes[i] + max(largestGroupToLeft[i], largestGroupToRight[i + sizes[i]]);
        ans = max(ans, sum);
    }
    fout << ans << endl;
    return 0;
}