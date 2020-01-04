// Test case path: [C:\Users\kento\Downloads\highcard_silver_dec15]
// highcard - Silver - December 2015-2016
// http://usaco.org/index.php?page=viewproblem2&cpid=571

#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("highcard.in");
    ofstream fout("highcard.out");
    int N;
    fin >> N;
    vector<bool> elsieHasIt;
    elsieHasIt.resize(2 * N);
    for (int i = 0; i < N; i++) {
        int a;
        fin >> a;
        a--;
        elsieHasIt[a] = true;
    }
    vector<int> elsie;
    vector<int> bessie;
    for (int i = 0; i < 2 * N; i++) {
        if (elsieHasIt[i]) {
            elsie.push_back(i);
        } else {
            bessie.push_back(i);
        }
    }
    int ans = 0;
    int bPoint = 0;
    for (int i = 0; i < N; i++) {
        while (bPoint < N && elsie[i] >= bessie[bPoint]) {
            bPoint++;
        }
        if (bPoint < N) {
            ans++;
            bPoint++;
        } else {
            break;
        }
    }
    fout << ans << endl;
    return 0;
}