// Test case path: [path]
// wormsort - Silver - January 2019-2020
// http://usaco.org/index.php?page=viewproblem2&cpid=992

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int width;
    int target;
};

struct Node {
    vector<Edge> edges;
};

vector<int> cows;
vector<Node> graph;
vector<int> widths;
int N, M;

bool alreadySorted() {
    for (int i = 0; i < N; i++) {
        if (i != cows[i]) {
            return false;
        }
    }
    return true;
}

void flood(vector<int> &sections, int section, int minWidth, int node) {
    queue<int> todo;
    todo.push(node);
    while (todo.size() > 0) {
        int top = todo.front();
        todo.pop();
        sections[top] = section;
        for (auto &edge : graph[top].edges) {
            if (sections[edge.target] == -1 && edge.width >= minWidth) {
                todo.push(edge.target);
            }
        }
    }
}

bool possible(int minWidth) {
    vector<int> sections = vector<int>(N, -1);
    int section = 0;
    for (int i = 0; i < N; i++) {
        if (sections[i] == -1) {
            flood(sections, section, minWidth, i);
            section++;
        }
    }
    for (int i = 0; i < N; i++) {
        if (sections[i] != sections[cows[i]]) {
            return false;
        }
    }
    for (int i = 0; i < N; i++) {
        if (sections[i] != sections[cows[i]]) {
            return false;
        }
    }
    return true;
}

int main() {
    ifstream fin("wormsort.in");
    ofstream fout("wormsort.out");
    fin >> N >> M;
    cows.resize(N);
    for (int i = 0; i < N; i++) {
        fin >> cows[i];
        cows[i]--;
    }
    if (alreadySorted()) {
        fout << -1 << endl;
        return 0;
    }
    graph.resize(N);
    widths.resize(M);
    for (int i = 0; i < M; i++) {
        int a, b, c;
        fin >> a >> b >> c;
        a--;
        b--;
        graph[a].edges.push_back({c, b});
        graph[b].edges.push_back({c, a});
        widths[i] = c;
    }
    sort(widths.begin(), widths.end());
    int lower = 0;
    int upper = M - 1;
    while (lower < upper - 1) {
        int mid = (lower + upper) / 2;
        if (possible(widths[mid])) {
            lower = mid;
        } else {
            upper = mid;
        }
    }
    if (possible(widths[upper])) {
        fout << widths[upper] << endl;
    } else {
        fout << widths[lower] << endl;
    }
    return 0;
}