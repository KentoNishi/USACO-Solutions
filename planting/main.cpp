/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: planting
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
    for(int i=0;i<stoi(inputstrings[0]);i++){
        Field field=Field();
        field.grass=i;
        fields.push_back(field);
    }
    for(int i=1;i<inputstrings.size();i++){
        vector<string> splitLine=split(inputstrings[i]," ");
        int larger=max(stoi(splitLine[0]),stoi(splitLine[1]));
        int smaller=min(stoi(splitLine[0]),stoi(splitLine[1]));
        fields[smaller-1].connections.push_back(larger-1);
        fields[larger-1].connections.push_back(smaller-1);
    }
    int ans=0;
    for(int i=0;i<fields.size();i++){
        ans=max(ans,visit(i));
    }
    fout << ans << endl;
    return 0;
}