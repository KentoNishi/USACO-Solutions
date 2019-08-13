// homework - Silver December 2017 - http://usaco.org/index.php?page=viewproblem2&cpid=762
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

struct compare {
    bool operator()(int a,int b) const { 
        return a < b;
    }
};

int main() {
    ofstream fout ("homework.out");
    ifstream fin ("homework.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> line2=split(inputstrings[1]," ");
    vector<int> points;
    for(string &item:line2){
        points.push_back(stoi(item));
    }
    int total=points[points.size()-1];
    int minimum=points[points.size()-1];
    float maximumMean=0;
    vector<int> answers;
    for(int k=points.size()-2;k>0;k--){
        total+=points[k];
        minimum=min(minimum,points[k]);
        float currentMean=float((total-minimum))/float(points.size()-1-k);
        if(currentMean>maximumMean){
            maximumMean=currentMean;
            answers={k};
        }else if(currentMean==maximumMean){
            answers.push_back(k);
        }
    }
    sort(answers.begin(),answers.end());
    for(int &k:answers){
        fout << k << endl;
    }
    return 0;
}
