// Test case path: [path]
// milkvisits - Silver - December 2019-2020
// http://usaco.org/index.php?page=viewproblem&cpid=956

#include <bits/stdc++.h>
using namespace std;
int N, M;

struct Farm {
    char type;
    vector<int> edges;
    int region = -1;
};

vector<Farm> farms;

void dfs(int i, int r) {
    if (farms[i].region >= 0) {
        return;
    }
    farms[i].region = r;
    for (auto &edge : farms[i].edges) {
        if (farms[edge].type == farms[i].type) {
            dfs(edge, r);
        }
    }
}

int main() {
    ifstream fin("milkvisits.in");
    ofstream fout("milkvisits.out");
    fin >> N >> M;
    string s;
    fin >> s;
    farms = vector<Farm>(N);
    for (int i = 0; i < N; i++) {
        farms[i].type = s[i];
    }
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        fin >> a >> b;
        a--;
        b--;
        farms[a].edges.push_back(b);
        farms[b].edges.push_back(a);
    }
    int regionID = 0;
    for (int i = 0; i < N; i++) {
        if (farms[i].region == -1) {
            dfs(i, regionID++);
        }
    }
    for (int i = 0; i < M; i++) {
        int a, b;
        char c;
        fin >> a >> b >> c;
        a--;
        b--;
        if (farms[a].region != farms[b].region || farms[a].type == c) {
            fout << 1;
        } else {
            fout << 0;
        }
    }
    fout << endl;
    return 0;
}