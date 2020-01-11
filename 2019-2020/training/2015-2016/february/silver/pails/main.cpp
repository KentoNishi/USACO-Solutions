// Test case path: [path]
// pails - Silver - February 2015-2016
// http://usaco.org/index.php?page=viewproblem2&cpid=620

#include <bits/stdc++.h>
using namespace std;

struct State {
    int bucket1;
    int bucket2;
    int moves;
    State(int b1, int b2, int m) {
        bucket1 = b1;
        bucket2 = b2;
        moves = m;
    }
};

bool operator<(State a, State b) {
    return make_tuple(a.bucket1, a.bucket2, a.moves) < make_tuple(b.bucket1, b.bucket2, b.moves);
}

int main() {
    ifstream fin("pails.in");
    ofstream fout("pails.out");
    int capacity1, capacity2, maxMoves, target;
    fin >> capacity1 >> capacity2 >> maxMoves >> target;
    map<State, bool> visited;
    queue<State> todo;
    todo.emplace(State(0, 0, 0));
    int ans = INT_MAX;
    while (todo.size() > 0) {
        State top = todo.front();
        todo.pop();
        ans = min(ans, abs(target - (top.bucket1 + top.bucket2)));
        if (top.moves + 1 > maxMoves) {
            continue;
        }
        int bucket2to1 = min(top.bucket1 + top.bucket2, capacity1) - top.bucket1;
        int bucket1to2 = min(top.bucket1 + top.bucket2, capacity2) - top.bucket2;
        State nextStates[] = {
            State(capacity1, top.bucket2, top.moves + 1),
            State(top.bucket1, capacity2, top.moves + 1),
            State(top.bucket1, 0, top.moves + 1),
            State(0, top.bucket2, top.moves + 1),
            State(top.bucket1 + bucket2to1, top.bucket2 - bucket2to1, top.moves + 1),
            State(top.bucket1 - bucket1to2, top.bucket2 + bucket1to2, top.moves + 1),
        };
        for (int k = 0; k < 6; k++) {
            if (!visited[nextStates[k]]) {
                visited[nextStates[k]] = true;
                todo.emplace(nextStates[k]);
            }
        }
    }
    fout << ans << endl;
    return 0;
}