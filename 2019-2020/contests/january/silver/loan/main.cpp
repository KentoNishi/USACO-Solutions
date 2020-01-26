// Test case path: [path]
// loan - Silver - January 2019-2020
// http://usaco.org/index.php?page=viewproblem2&cpid=991

#include <bits/stdc++.h>
using namespace std;

long long N, K, M;

bool tryIt(long long X) {
    long long given = 0;
    for (long long day = 0; day < K;) {
        long long Y = (N - given) / X;
        if ((N - given) / max(Y, M) > (K - day)) {
            return false;
        }
        if (Y <= M) {
            given += (K - day) * M;
            return given >= N;
        }
        long long howMuchUntilChange = (N - given) % X;
        if (howMuchUntilChange >= 2 * Y) {
            long long toGive = Y * (howMuchUntilChange / Y);
            given += toGive;
            day += toGive / Y;
        } else {
            given += Y;
            day++;
        }
        if (given >= N) {
            return false;
        }
    }
    return given >= N;
}

int main() {
    ifstream fin("loan.in");
    ofstream fout("loan.out");
    fin >> N >> K >> M;
    long long upper = N;
    long long lower = 1;
    long long ans = K;
    while (lower < upper - 1) {
        long long avg = (upper + lower) / 2;
        if (tryIt(avg)) {
            lower = avg;
            ans = max(ans, avg);
        } else {
            upper = avg;
        }
    }
    if (!tryIt(upper)) {
        fout << lower << endl;
    } else {
        fout << upper << endl;
    }
    return 0;
}