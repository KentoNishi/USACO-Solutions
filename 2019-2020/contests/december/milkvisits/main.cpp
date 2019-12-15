// Test case path: [path]
// milkvisits - Division - Month Season
// http://usaco.org/index.php?page=viewproblem&cpid=956

#include <bits/stdc++.h>
using namespace std;
int N, M;

struct Farm {
    char type;
    vector<int> edges;
    bool visited;
};

vector<Farm> farms;
//vector<vector<pair<bool,bool>>> mem;

bool flood(int a, int b, bool &H, bool &G) {
    if (a == b) {
        H = farms[a].type == 'H';
        G = farms[a].type == 'G';
        return true;
    }
    if (farms[a].visited) {
        return false;
    }
    farms[a].visited = true;
    for (auto &edge : farms[a].edges) {
        if (flood(edge, b, H, G)) {
            if (!H) {
                H = (farms[edge].type == 'H' || farms[a].type == 'H');
            }
            if (!G) {
                G = (farms[edge].type == 'G' || farms[a].type == 'G');
            }
            return true;
        }
    }
    return false;
}

int main() {
    ifstream fin("milkvisits.in");
    ofstream fout("milkvisits.out");
    fin >> N >> M;
    string s;
    fin >> s;
    farms = vector<Farm>(N);
    //    mem=vector<vector<pair<bool,bool>>>(N,vector<pair<bool,bool>>(N));
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
    for (int i = 0; i < M; i++) {
        int a, b;
        char c;
        bool H, G = false;
        fin >> a >> b >> c;
        a--;
        b--;
        flood(a, b, H, G);
        if (H && c == 'H') {
            fout << 1;
        } else if (G && c == 'G') {
            fout << 1;
        } else {
            fout << 0;
        }
        for (int k = 0; k < N; k++) {
            farms[k].visited = false;
        }
    }
    return 0;
}