// Test case path: [path]
// moobuzz - Silver - December 2019-2020
// http://usaco.org/index.php?page=viewproblem&cpid=954

#include <bits/stdc++.h>
using namespace std;
int N;

vector<int> first8;

int main() {
    ifstream fin("moobuzz.in");
    ofstream fout("moobuzz.out");
    fin >> N;
    for (int i = 1; i <= 15; i++) {
        if (i % 3 > 0 && i % 5 > 0) {
            first8.push_back(i);
        }
    }
    fout << first8[(N - 1) % 8] + 15 * ((N - 1) / 8) << endl;
    return 0;
}