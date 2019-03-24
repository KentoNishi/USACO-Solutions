//http://usaco.org/index.php?page=viewproblem2&cpid=920
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <bitset>
#include <tuple>
#include <cmath>
#include <unordered_map>
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

int N[100001];
vector<int> S[100001];
vector<int> D[100001];
bool bad=false;

void visit(int x, int v){
	N[x] = v;
	for (auto n : S[x]) {
		if (N[n] == 3-v){
			bad = true; 
		}
		if (N[n] == 0){
			visit(n, v);
		}
	}
	for (auto n : D[x]) {
		if (N[n] == v){
			bad = true; 
		}
		if (N[n] == 0){
			visit(n, 3-v);
		}
	}  
}
 

int main() {
    vector<string> inputstrings;
    string contents;
	ifstream fin("revegetate.in");
	ofstream fout("revegetate.out");
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
	for(int i=1;i<inputstrings.size();i++){
		vector<string> splitln=split(inputstrings[i]," ");
		int a=stoi(splitln[1]);
		int b=stoi(splitln[2]);
		bool type=splitln[0]=="S";//true=same,false=different
		if(type){
			S[a].push_back(b);
			S[b].push_back(a);
		}else{
			D[a].push_back(b);
			D[b].push_back(a);
		}
	}
	int ans=0;
	for(int i=1;i<=stoi(split(inputstrings[0]," ")[0]);i++){
		if(!N[i]){
			visit(i,1);
			ans++;
		}
	}
	for(int i=0;i<4;i++){
		cout << N[i] << endl;
	}
	if(bad){
		fout << "0" << endl;
	}else{
		string out="1";
		for(int i=0;i<ans;i++){
			out+="0";
		}
		fout << out << endl;
	}
	return 0;
}