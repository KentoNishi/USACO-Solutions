//http://usaco.org/index.php?page=viewproblem2&cpid=692
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

char parse(string str, long long index){
    if(index<str.length()){
        return str[index];
    }
    long long length=str.length();
    while(length*2<=index){
        length*=2;
    }
    if(length==index){
        return parse(str,index-1);
    }else{
        return parse(str,index-length-1);
    }
}

int main() {
    ofstream fout ("cowcode.out");
    ifstream fin ("cowcode.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> ln=split(inputstrings[0]," ");
    string str=ln[0];
    long long index=stoll(ln[1])-1;
    fout << parse(str,index)<< endl;
    return 0;
}