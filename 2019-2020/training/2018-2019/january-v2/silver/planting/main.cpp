// Test case path: [path]
// planting - Silver - January 2018-2019
// http://usaco.org/index.php?page=viewproblem2&cpid=894

#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("planting.in");
    ofstream fout("planting.out");
    int N;
    fin >> N;
    vector<int> graph;
    graph.resize(N);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        fin >> a >> b;
        a--;
        b--;
        graph[a]++;
        graph[b]++;
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        ans = max(ans, graph[i] + 1);
    }
    fout << ans << endl;
    return 0;
}