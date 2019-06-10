//http://usaco.org/index.php?page=viewproblem2&cpid=918
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <bitset>
#include <tuple>
#include <cmath>
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

int grid[1001][1001];
int main() {
    ofstream fout ("paintbarn.out");
    ifstream fin ("paintbarn.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> firstLine=split(inputstrings[0]," ");
    int match=stoi(firstLine[1]);
    for(int i=1;i<inputstrings.size();i++){
        vector<string> line=split(inputstrings[i]," ");
        int a=stoi(line[0]);
        int b=stoi(line[1]);
        int c=stoi(line[2]);
        int d=stoi(line[3]);
        grid[a][b]++;
        grid[c][d]++;
        grid[c][b]--;
        grid[a][d]--;
    }
    int ans=0;
    for(int x=0;x<1001;x++){
        for(int y=0;y<1001;y++){
            if(x>0){
                grid[x][y]+=grid[x-1][y];
            }
            if(y>0){
                grid[x][y]+=grid[x][y-1];
            }
            if(x>0&&y>0){
                grid[x][y]-=grid[x-1][y-1];
            }
            if(grid[x][y]==match){
                ans++;
            }
        }
    }
    fout << ans << endl;
	return 0;
}