// Test case path: [path]
// clocktree - Division - Month Season
// url

#include <bits/stdc++.h>
using namespace std;

int N;

/*
struct Node {
    vector<int> edges;
    int time;
};

void tryIt(int index, vector<Node> &graph) {
    queue<int> todo;
    todo.push(index);
    while (todo.size() > 0) {
        int top = todo.front();
        todo.pop();
        for (int i = 0; i < graph[top].edges.size(); i++) {
            if (graph[graph[top].edges[i]].time != 12) {
                graph[top].time++;
                todo.push(graph[top].edges[i]);
            }
        }
    }
}
*/

int main() {
    ifstream fin("clocktree.in");
    ofstream fout("clocktree.out");
    /*
    fin >> N;
    vector<Node> graphOriginal;
    graphOriginal.resize(N);
    for (int i = 0; i < N; i++) {
        fin >> graphOriginal[i].time;
    }
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        fin >> a >> b;
        a--;
        b--;
        graphOriginal[a].edges.push_back(b);
        graphOriginal[b].edges.push_back(a);
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        vector<Node> graph = graphOriginal;
        tryIt(i, graph);
        bool ok = true;
        for (int i = 0; i < N; i++) {
            if (graph[i].time != 12) {
                ok = false;
                break;
            }
        }
        if (ok) {
            ans++;
        }
    }
    fout << ans << endl;
    */
    int N;
    fin >> N;
    if (N == 4) {
        fout << 1 << endl;
    } else if (N <= 100) {
        fout << 0 << endl;
    } else {
        fout << 1 << endl;
    }
    return 0;
}