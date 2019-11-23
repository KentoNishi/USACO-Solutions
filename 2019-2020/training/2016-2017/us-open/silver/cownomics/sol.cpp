#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;

int N, M;
string spotty[500], plain[500];
int S[500][50], P[500][50], A[64];

bool test_location(int j1, int j2, int j3) {
    bool good = true;
    for (int i = 0; i < N; i++)
        A[S[i][j1] * 16 + S[i][j2] * 4 + S[i][j3]] = 1;
    for (int i = 0; i < N; i++)
        if (A[P[i][j1] * 16 + P[i][j2] * 4 + P[i][j3]])
            good = false;
    for (int i = 0; i < N; i++)
        A[S[i][j1] * 16 + S[i][j2] * 4 + S[i][j3]] = 0;
    return good;
}

int main(void) {
    ifstream fin("cownomics.in");
    ofstream fout("cownomics.out");
    fin >> N >> M;
    for (int i = 0; i < N; i++) {
        fin >> spotty[i];
        for (int j = 0; j < M; j++) {
            if (spotty[i][j] == 'A')
                S[i][j] = 0;
            if (spotty[i][j] == 'C')
                S[i][j] = 1;
            if (spotty[i][j] == 'G')
                S[i][j] = 2;
            if (spotty[i][j] == 'T')
                S[i][j] = 3;
        }
    }
    for (int i = 0; i < N; i++) {
        fin >> plain[i];
        for (int j = 0; j < M; j++) {
            if (plain[i][j] == 'A')
                P[i][j] = 0;
            if (plain[i][j] == 'C')
                P[i][j] = 1;
            if (plain[i][j] == 'G')
                P[i][j] = 2;
            if (plain[i][j] == 'T')
                P[i][j] = 3;
        }
    }
    int answer = 0;
    for (int j1 = 0; j1 < M; j1++)
        for (int j2 = j1 + 1; j2 < M; j2++)
            for (int j3 = j2 + 1; j3 < M; j3++)
                if (test_location(j1, j2, j3))
                    cout << j1 << " " << j2 << " " << j3 << " is good " << endl;
                    answer++;
    fout << answer << "\n";
    return 0;
}