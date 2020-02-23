// Test case path: [path]
// revegetate - Silver - February 2018-2019
// http://usaco.org/index.php?page=viewproblem2&cpid=920

#include <bits/stdc++.h>
using namespace std;

int N, M;

struct Edge {
    int target;
    char condition;
};

struct Node {
    vector<Edge> edges;
    int type = -1;
};

vector<Node> graph;

void visit(int index, int type, bool &ok) {
    if (!ok) {
        return;
    }
    if (graph[index].type != -1) {
        if (graph[index].type != type) {
            ok = false;
        }
        return;
    }
    graph[index].type = type;
    for (auto &edge : graph[index].edges) {
        if (edge.condition == 'D') {
            visit(edge.target, 1 - type, ok);
        } else if (edge.condition == 'S') {
            visit(edge.target, type, ok);
        }
    }
}

int main() {
    ifstream fin("revegetate.in");
    ofstream fout("revegetate.out");
    fin >> N >> M;
    graph.resize(N);
    for (int i = 0; i < M; i++) {
        char a;
        int b, c;
        fin >> a >> b >> c;
        b--;
        c--;
        graph[b].edges.push_back({c, a});
        graph[c].edges.push_back({b, a});
    }
    int regions = 0;
    for (int i = 0; i < N; i++) {
        if (graph[i].type == -1) {
            bool ok = true;
            visit(i, 0, ok);
            if (ok) {
                regions++;
            } else {
                fout << 0 << endl;
                return 0;
            }
        }
    }
    fout << 1;
    for (int i = 0; i < regions; i++) {
        fout << 0;
    }
    fout << endl;
    return 0;
}