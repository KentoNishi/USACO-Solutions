// Test case path: [path]
// balancing - Division - Month Season
// url

#include <bits/stdc++.h>
using namespace std;

int ans;
vector<pair<int, int>> points;
int N;

void test(int x) {
    /*
        0 1
        2 3
    */
    cout << "x is " << x << endl;
    vector<vector<int>> prefix = vector<vector<int>>(4, vector<int>(N + 1));
    for (int i = 0; i < N; i++) {
        if (points[i].first > x) {
            prefix[1][i + 1]++;
        } else {
            prefix[0][i + 1]++;
        }
        prefix[0][i + 1] += prefix[0][i];
        prefix[1][i + 1] += prefix[1][i];
    }
    for (int i = N - 1; i >= 0; i--) {
        if (points[i].first > x) {
            prefix[3][i]++;
        } else {
            prefix[2][i]++;
        }
        prefix[2][i] += prefix[2][i + 1];
        prefix[3][i] += prefix[3][i + 1];
    }
    for (int i = 0; i <= N; i++) {
        while (i > 0 && i <= N && points[i].second == points[i - 1].second) {
            i++;
        }
        int local = prefix[0][i];
        for (int k = 0; k < 4; k++) {
            local = max(local, prefix[k][i]);
        }
        for (int k = 0; k < 4; k++) {
            cout << prefix[k][i] << " ";
        }
        cout << endl;
        ans = min(local, ans);
    }
}

int main() {
    ifstream fin("balancing.in");
    ofstream fout("balancing.out");
    fin >> N;
    ans = N;
    points = vector<pair<int, int>>(N);
    for (int i = 0; i < N; i++) {
        fin >> points[i].first >> points[i].second;
    }
    sort(points.begin(), points.end());
    if (N % 2 == 1) {
        int num1 = points[N / 2].first - 1;
        int num2 = points[N / 2].first + 1;
        sort(points.begin(), points.end(), [](pair<int, int> a, pair<int, int> b) { return a.second < b.second; });
        test(num1);
        test(num2);
    } else {
        int num = (points[N / 2].first + points[N / 2 - 1].first) / 2;
        sort(points.begin(), points.end(), [](pair<int, int> a, pair<int, int> b) { return a.second < b.second; });
        test(num);
    }
    fout << ans << endl;
    return 0;
}