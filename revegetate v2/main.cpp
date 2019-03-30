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

struct Value{
	vector<int> same;
	vector<int> different;
	int id=0;
};

Value values[100001];
bool impossible=false;
void visit(int x, int v){
	values[x].id=v;
	for(auto s: values[x].same){
		if(values[s].id==3-v){
			impossible=true;
			return;
		}
		if(values[s].id==0){
			visit(s,v);
		}
	}
	for(auto d: values[x].different){
		if(values[d].id==v){
			impossible=true;
			return;
		}
		if(values[d].id==0){
			visit(d,3-v);
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
			values[a].same.push_back(b);
			values[b].same.push_back(a);
		}else{
			values[a].different.push_back(b);
			values[b].different.push_back(a);
		}
	}
	int ans=0;
	int nodes=stoi(split(inputstrings[0]," ")[0]);
	for(int i=1;i<=nodes;i++){
		if(values[i].id==0){
			visit(i,1);
			ans++;
		}
	}
	if(impossible){
		fout << 0 << endl;
	}else{
		fout << 1;
		for(int i=0;i<ans;i++){
			fout << 0;
		}
		fout << endl;
	}
	return 0;
}