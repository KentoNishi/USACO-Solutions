// Test case path: [path]
// clocktree - Silver - February 2019-2020
// http://usaco.org/index.php?page=viewproblem2&cpid=1016

#include <bits/stdc++.h>
using namespace std;

int N;

struct Node {
    vector<int> edges;
    int time;
};

int dfs(int index, vector<bool> &visited, vector<Node> &graph) {
    if (visited[index]) {
        return 0;
    }
    visited[index] = true;
    int currentTime = graph[index].time + 1;
    currentTime %= 12;
    int branchCount = 0;
    for (auto &edge : graph[index].edges) {
        if (!visited[edge]) {
            branchCount++;
            currentTime += 12 - dfs(edge, visited, graph);
            currentTime %= 12;
        }
    }
    return (currentTime + branchCount) % 12;
}

int main() {
    ifstream fin("clocktree.in");
    ofstream fout("clocktree.out");
    fin >> N;
    vector<Node> graph = vector<Node>(N);
    for (int i = 0; i < N; i++) {
        fin >> graph[i].time;
        graph[i].time %= 12;
    }
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        fin >> a >> b;
        a--;
        b--;
        graph[a].edges.push_back(b);
        graph[b].edges.push_back(a);
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        vector<bool> visited = vector<bool>(N);
        int time = dfs(i, visited, graph);
        if (time == 1 || time == 2) {
            ans++;
        }
    }
    fout << ans << endl;
    return 0;
}