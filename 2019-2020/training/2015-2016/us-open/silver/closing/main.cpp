// Test case path: [path]
// closing - Silver - US-Open 2015-2016
// http://usaco.org/index.php?page=viewproblem2&cpid=644

#include <bits/stdc++.h>
using namespace std;

int N, M;

struct Node {
    bool visited = false;
    vector<int> edges;
    bool bad = false;
};

vector<Node> graph;

int flood(int i) {
    queue<int> todo;
    todo.emplace(i);
    graph[i].visited = true;
    int total = 0;
    while (todo.size() > 0) {
        int top = todo.front();
        todo.pop();
        total++;
        for (auto &edge : graph[top].edges) {
            if (!graph[edge].visited && !graph[edge].bad) {
                graph[edge].visited = true;
                todo.emplace(edge);
            }
        }
    }
    // cout << total << endl;
    return total;
}

int main() {
    ifstream fin("closing.in");
    ofstream fout("closing.out");
    fin >> N >> M;
    graph.resize(N);
    for (int i = 0; i < M; i++) {
        int a, b;
        fin >> a >> b;
        a--;
        b--;
        graph[a].edges.push_back(b);
        graph[b].edges.push_back(a);
    }
    fout << (flood(0) == N ? "YES" : "NO") << endl;
    set<int> good;
    for (int i = 0; i < N; i++) {
        good.insert(i);
    }
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N; j++) {
            graph[j].visited = false;
        }
        int a;
        fin >> a;
        a--;
        graph[a].bad = true;
        good.erase(good.find(a));
        int total = flood(*good.begin());
        if (total != good.size()) {
            fout << "NO" << endl;
        } else {
            fout << "YES" << endl;
        }
    }
    return 0;
}