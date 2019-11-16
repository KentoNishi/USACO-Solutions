// sort - Silver - US-Open 2017-2018
// http://usaco.org/index.php?page=viewproblem2&cpid=834

#include <bits/stdc++.h>
using namespace std;

struct compare {
    bool operator()(pair<int, int> a, pair<int, int> b) const {
        if (a.first != b.first) {
            return a.first < b.first;
        }
        return a.second < b.second;
    }
};

int main() {
    ofstream fout("sort.out");
    ifstream fin("sort.in");
    int N;
    fin >> N;
    vector<pair<int, int>> nums = vector<pair<int, int>>(N);
    // num, loc
    for (int i = 0; i < N; i++) {
        int a;
        fin >> a;
        nums[i] = (make_pair(a, i));
    }
    sort(nums.begin(), nums.end(), compare());
    int ans = 0;
    for (int i = 0; i < N; i++) {
        cout << nums[i].first << " " << nums[i].second << endl;
        ans = max(ans, nums[i].second - i);
    }
    fout << ans + 1 << endl;
    return 0;
}