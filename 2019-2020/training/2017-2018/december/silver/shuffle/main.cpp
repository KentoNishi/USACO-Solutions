// shuffle - Silver - December 2017-2018 - http://usaco.org/index.php?page=viewproblem2&cpid=764

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

int main() {
    ofstream fout("shuffle.out");
    ifstream fin("shuffle.in");
    int N;
    fin >> N;
    vector<int> shuffles = vector<int>(N);
    vector<int> cowCount(N, 0);
    for (int i = 0; i < N; i++) {
        int shuffle;
        fin >> shuffle;
        shuffles[i] = shuffle - 1;
        cowCount[shuffles[i]]++;
    }
    queue<int> emptyCells;
    int ans = N;
    for (int i = 0; i < N; i++) {
        if (cowCount[i] == 0) {
            emptyCells.push(i);
            ans--;
        }
    }
    while (emptyCells.size() > 0) {
        int &current = emptyCells.front();
        emptyCells.pop();
        cowCount[shuffles[current]]--;
        if (cowCount[shuffles[current]] == 0) {
            ans--;
            emptyCells.push(shuffles[current]);
        }
    }
    fout << ans << endl;
    return 0;
}