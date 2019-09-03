#include <fstream>
#include <iostream>
using namespace std;

int N;
char grid[1000][1000];

int num(int i1, int j1, int i2, int j2, int b) {
    int total = 0;
    for (int i = i1; i <= i2; i++)
        for (int j = j1; j <= j2; j++)
            if (grid[i][j] == b)
                total++;
    cout << total << endl;
    return total;
}

int main(void) {
    ifstream fin("leftout.in");
    string s;
    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> s;
        for (int j = 0; j < N; j++)
            grid[i][j] = s[j] == 'L';
    }

    // Flip columns and rows so top row and left column all zero
    for (int i = 1; i < N; i++) {
        grid[i][0] = grid[i][0] ^ grid[0][0];
        for (int j = 1; j < N; j++)
            grid[i][j] = grid[i][j] ^ grid[0][j] ^ grid[i][0];
    }

    ofstream fout("leftout.out");
    if (num(1, 1, N - 1, N - 1, 0) == 0) {
        fout << "1 1\n";
        return 0;
    }
    if (num(1, 1, N - 1, N - 1, 1) == N - 1) {
        for (int j = 1; j < N; j++)
            if (num(1, j, N - 1, j, 1) == N - 1) {
                fout << "1 " << j + 1 << "\n";
                return 0;
            }
        for (int i = 1; i < N; i++)
            if (num(i, 1, i, N - 1, 1) == N - 1) {
                fout << i + 1 << " 1\n";
                return 0;
            }
        fout << "-1\n";
        return 0;
    }
    if (num(1, 1, N - 1, N - 1, 1) != 1) {
        fout << "-1\n";
        return 0;
    }
    for (int i = 1; i < N; i++)
        for (int j = 1; j < N; j++)
            if (grid[i][j] == 1) {
                fout << i + 1 << " " << j + 1 << "\n";
            }
    return 0;
}