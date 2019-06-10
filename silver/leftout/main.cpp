//http://usaco.org/index.php?page=viewproblem2&cpid=942
/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: leftout
LANG: C++14                 
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <array>
using namespace std;

vector<string> split(string str, string character){
    vector<string> result;
    long long s=0;
    long long i=0;
    while(i<str.length()){
        if(str[i]==character[0]||i==str.length()-1){
            long long x=i-s;
            if(i==str.length()-1){
                x++;
            }
            result.push_back(str.substr(s,x));
            s=i+1;
        }
        i++;
    }
    return result;
}

vector<vector<int>> grid;

int num(int i1, int j1, int i2, int j2, int b)
{
    int total = 0;
    for (int i = i1; i <= i2; i++){
        for (int j = j1; j <= j2; j++){
            if (grid[i][j] == b){
                total++;
            }
        }
    }
    return total;
}

int main() {
    ofstream fout ("leftout.out");
    ifstream fin ("leftout.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    for(int i=1;i<inputstrings.size();i++){
        grid.push_back({});
        for(int k=0;k<stoi(inputstrings[0]);k++){
            grid[i-1].push_back(string(1,inputstrings[i][k])=="R"?0:1);
        }
    }
    for (int i = 1; i < grid.size(); i++)
    {
        grid[i][0] = grid[i][0] ^ grid[0][0];
//        cout << i << ",0-->"<<grid[i][0] << endl;
        for (int j = 1; j < grid.size(); j++){
            grid[i][j] = grid[i][j] ^ grid[0][j] ^ grid[i][0];
//            cout << i <<","<< j << "-->"<<grid[i][j]<< endl;
        }
    }
    for(int y=0;y<grid.size();y++){
        for(int x=0;x<grid.size();x++){
            cout << grid[y][x] << " ";
        }
        cout << endl;
    }
    if(num(1,1,grid.size()-1,grid.size()-1,0)==0){
        fout << "1 1" << endl;
        return 0;
    }
    if(num(1,1,grid.size()-1,grid.size()-1,1)==grid.size()-1){
        for(int j=1;j<grid.size();j++){
            if(num(1,j,grid.size()-1,j,1)==grid.size()-1){
                fout << "1 " << j+1 << endl;
                return 0;
            }
        }
        for(int i=1;i<grid.size();i++){
            if(num(i,1,i,grid.size()-1,1)==grid.size()-1){
                fout << i+1 <<  " 1" << endl;
                return 0;
            }
        }
        fout << -1 << endl;
        return 0;
    }
    if(num(1,1,grid.size()-1,grid.size()-1,1)!=1){
        fout << -1 << endl;
        return 0;
    }
    for(int x=1;x<grid.size();x++){
        for(int y=1;y<grid.size();y++){
            if(grid[x][y]==1){
                fout<<x+1<<" "<<y+1<<endl;
                return 0;
            }
        }
    }
    return 0;
}