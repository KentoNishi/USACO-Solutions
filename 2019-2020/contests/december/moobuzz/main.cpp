// Test case path: [path]
// moobuzz - Division - Month Season
// http://usaco.org/index.php?page=viewproblem&cpid=954

#include <bits/stdc++.h>
using namespace std;
long long N;

long long indexOf(long long m) {
    return m - (m / 3) - (m / 5) + (m / 15);
}

long long binarySearch(long long l, long long h) {
    long long m = (l + h) / 2;
    long long index = indexOf(m);
    if (abs(h - l) <= 1) {
        if (indexOf(h) == N) {
            return h;
        } else {
            return l;
        }
    }
    if (index == N) {
        return m;
    } else if (index < N) {
        return binarySearch(m, h);
    } else {
        return binarySearch(l, m);
    }
}

int main() {
    ifstream fin("moobuzz.in");
    ofstream fout("moobuzz.out");
    fin >> N;
    fout << binarySearch(N - 1, pow(2, 32)) << endl;
    return 0;
}