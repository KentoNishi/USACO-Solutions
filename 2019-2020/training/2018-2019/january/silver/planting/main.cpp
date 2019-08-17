// planting - Silver - January 2018-2019 -http://usaco.org/index.php?page=viewproblem2&cpid=894

/*
    Summary:
        Given a non-directed graph with N nodes and N-1 edges,
        find the maximum amount of classes neccessary.
        Every node connected to any other node by a distance
        of less than or equal to 2 edges must not be of the same class.
    Solution:
        Build the graph from the input data.
        Find the maximum of (number of edges+1) in the graph.
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct Node {
    int edges = 0;
};

vector<Node> graph;

int main() {
    ofstream fout("planting.out");
    ifstream fin("planting.in");
    int N;
    /*
        N: Number of nodes in the graph
    */
    fin >> N;
    graph = vector<Node>(N);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        fin >> a >> b;
        graph[a - 1].edges++;
        graph[b - 1].edges++;
    }
    int answer = 0;
    for (int i = 0; i < graph.size(); i++) {
        answer = max(answer, graph[i].edges + 1);
    }
    cout << answer << endl;
    fout << answer << endl;
    return 0;
}