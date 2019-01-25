/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: planting
LANG: C++14                 
*/
/* LANG can be C++11 or C++14 for those more recent releases */
//http://usaco.org/index.php?page=viewproblem2&cpid=894
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

struct Field{
    vector<int> connections;
    bool seen=false;
    int grass;
};

vector<Field> fields;

int visit(int id,int level=0,int prev=-1){
    int ret=0;
    if(fields[id].seen==false){
        ret++;
        fields[id].seen=true;
        if(level<=1){
            for(int i=0;i<fields[id].connections.size();i++){
                if(fields[id].connections[i]!=prev){
                    ret+=visit(fields[id].connections[i],level+1,id);
                }
            }
        }
    }
    return ret;
}

int main() {
    ofstream fout ("planting.out");
    ifstream fin ("planting.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    int nodes[100000];
    for(int i=1;i<inputstrings.size();i++){
        vector<string> spltln=split(inputstrings[i]," ");
        nodes[stoi(spltln[0])-1]++;
        nodes[stoi(spltln[1])-1]++;
    }
    int maximum=0;
    for(int i=0;i<100000;i++){
        maximum=max(maximum,nodes[i]);
    }
    fout << maximum+1 << endl;
    return 0;
}