// Test case path: [path]
// cowcode - Silver - January 2016-2017
// http://usaco.org/index.php?page=viewproblem2&cpid=692

#include <bits/stdc++.h>
using namespace std;

string s;
long long N;

char findAns(long long index) {
    long long start = s.size();
    while (start * 2 <= index) {
        start *= 2;
    }
    while (true) {
        // cout << index << " <= " << start << endl;
        if (index < s.size()) {
            return s[index];
        }
        long long indexInRight = index - start;
        long long indexInLeft = indexInRight - 1;
        if (indexInLeft == -1) {
            indexInLeft = start - 1;
        }
        index = indexInLeft;
        while (start > index) {
            start /= 2;
        }
    }
}

int main() {
    ifstream fin("cowcode.in");
    ofstream fout("cowcode.out");
    fin >> s >> N;
    fout << findAns(N - 1) << endl;
    /*
    for (long long i = 1; i <= N; i++) {
        fout << findAns(i - 1) << endl;
    }
    */
    return 0;
}