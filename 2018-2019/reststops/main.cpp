//http://usaco.org/index.php?page=viewproblem2&cpid=810
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

struct Stop{
    long long location;
    long long tastiness;
    bool max;
};

int  main() {
    ofstream fout ("reststops.out");
    ifstream fin ("reststops.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> firstLine=split(inputstrings[0]," ");
    long long distance=stoi(firstLine[0]);
    long long speedJohn=stoi(firstLine[2]);
    long long speedBessie=stoi(firstLine[3]);
    vector<Stop> stops;
    for(long long i=1;i<inputstrings.size();i++){
        Stop stop=Stop();
        vector<string> line=split(inputstrings[i]," ");
        stop.location=stoi(line[0]);
        stop.tastiness=stoi(line[1]);
        stops.push_back(stop);
    }
    
    long long maximum=0;
    for(long long i=stops.size()-1;i>=0;i--){
        if(stops[i].tastiness>maximum){
            stops[i].max=true;
            maximum=stops[i].tastiness;
        }else{
            stops[i].max==false;
        }
    }
    long long total=0;
    long long last=0;
    long long secsJohn=0;
    long long secsBessie=0;
    for(long long i=0;i<stops.size();i++){
        if(stops[i].max){
            long long dist=stops[i].location-last;
            secsBessie+=dist*speedBessie;
            secsJohn+=dist*speedJohn;
            total+=stops[i].tastiness*(secsJohn-secsBessie);
            secsBessie=secsJohn;
            last=stops[i].location;
        }
    }
    fout << total << endl;
    return 0;
}