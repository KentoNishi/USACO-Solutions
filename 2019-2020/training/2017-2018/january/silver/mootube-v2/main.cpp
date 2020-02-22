// Test case path: [path]
// mootube - Silver - January 2017-2018
// http://usaco.org/index.php?page=viewproblem2&cpid=788

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int weight;
    int dest;
};

struct Node {
    vector<Edge> edges;
};

int N, Q;
vector<Node> graph;

void countVideos(int start, int &count, int K, vector<bool> &visited) {
    if (visited[start]) {
        return;
    }
    count++;
    visited[start] = true;
    for (auto &edge : graph[start].edges) {
        if (edge.weight >= K) {
            countVideos(edge.dest, count, K, visited);
        }
    }
}

int main() {
    ifstream fin("mootube.in");
    ofstream fout("mootube.out");
    fin >> N >> Q;
    graph.resize(N);
    for (int i = 0; i < N - 1; i++) {
        int a, b, c;
        fin >> a >> b >> c;
        a--;
        b--;
        graph[a].edges.push_back({c, b});
        graph[b].edges.push_back({c, a});
    }
    for (int i = 0; i < Q; i++) {
        int count = 0;
        int start;
        int K;
        fin >> K >> start;
        start--;
        vector<bool> visited = vector<bool>(N);
        countVideos(start, count, K, visited);
        fout << count - 1 << endl;
    }
    return 0;
}