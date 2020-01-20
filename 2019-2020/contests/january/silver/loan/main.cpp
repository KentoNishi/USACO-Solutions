// Test case path: [path]
// loan - Division - Month Season
// url

#include <bits/stdc++.h>
using namespace std;

long long N, K, M;

bool tryIt(long long X) {
    long long given = 0;
    for (long long day = 0; day < K; day++) {
        long long Y = (N - given) / X;
        if ((N - given) / max(Y, M) > (K - day)) {
            return false;
        }
        if (Y <= M) {
            given += (K - day) * M;
            return given >= N;
        }
        given += Y;
        if (given >= N) {
            return false;
        }
    }
    // cout << given << " for " << X << endl;
    if (given >= N) {
        return true;
    }
    return false;
}

int main() {
    ifstream fin("loan.in");
    ofstream fout("loan.out");
    fin >> N >> K >> M;
    long long upper = N;
    long long lower = 1;
    long long ans = N;
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