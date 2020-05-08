//http://usaco.org/index.php?page=viewproblem2&cpid=858
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <stdio.h> 
#include <string.h> 
#include <typeinfo>
#include <numeric>
#include <algorithm>
#include <cmath>
using namespace std;

vector<string> split(string str, string character){
    vector<string> result;
    int s=0;
    int i=0;
    while(i<str.length()){
        if(str[i]==character[0]||i==str.length()-1){
            int x=i-s;
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

struct comp {
  bool operator()( array<int,2> a, array<int,2> b ) const { 
    return a[0] < b[1];
  }
};


vector<vector<vector<int>>> splitter(vector<int> riders,int buses,int maximum){
    int minimum=maximum-(buses*maximum-riders.size());
    minimum=(minimum>0)?minimum:1;
    vector<vector<vector<int>>> returns;
    if(riders.size()>0){
        if(buses>1){
    //        cout << minimum <<":::"<< maximum << endl;
            for(int ppl=minimum;ppl<=maximum&&ppl<=riders.size();ppl++){
                vector<int> people(riders.begin(),riders.begin()+ppl);
                vector<int> left(riders.begin()+ppl,riders.end());
                vector<vector<vector<int>>> res=splitter(left,buses-1,maximum);
    //            cout << people.size() << " " << left.size() << " " << res.size() << endl;
                for(int i=0;i<res.size();i++){
                    vector<vector<int>> clone={people};
                    clone.insert(clone.end(),res[i].begin(),res[i].end());
                    returns.push_back(clone);
                }
            }
        }else{
            returns.push_back({riders});
        }
    }
    return returns;
}

/*
if(buses>1){
        for(int ppl=minimum;ppl<=maximum;ppl++){
            vector<int> people(riders.begin(),riders.begin()+ppl);
            vector<int> left(riders.begin()+ppl,riders.end());
            vector<vector<vector<int>>> res=splitter(left,buses-1,maximum);
            for(int i=0;i<res.size();i++){
                vector<vector<int>> clone=res[i];
                clone.insert(clone.begin(),people.begin(),people.end());
                returns.push_back(clone);
            }
        }
    }else{
        returns.push_back({riders});
    }
    return returns;
    */

int main() {
    ofstream fout ("convention.out");
    ifstream fin ("convention.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
	vector<int> params;
	vector<int> cows;
	for(int k=0;k<2;k++){
		vector<string> spl=split(inputstrings[k]," ");
		for(int i=0;i<spl.size();i++){
			if(k==0){
				params.push_back(stoi(spl[i]));
			}else if(k==1){
				cows.push_back(stoi(spl[i]));
			}
		}
	}
	sort(cows.begin(),cows.end());
    vector<vector<vector<int>>> all=splitter(cows,params[1],params[2]);
    int global=-1;
    for(int i=0;i<all.size();i++){
        int local=0;
        for(int k=0;k<all[i].size();k++){
            if(all[i][k].size()>0){
                int last=all[i][k][all[i][k].size()-1];
                int first=all[i][k][0];
                if(last-first>local){
                    local=last-first;
                }
            }
            for(int j=0;j<all[i][k].size();j++){
                cout << all[i][k][j] << " ";
            }
            cout << "  ";
        }
        cout << endl;
        if(global==-1||local<global){
            global=local;
        }
    }
    cout << global << endl;
    fout << global << endl;
    return 0;
}

