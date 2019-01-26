/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: rental
LANG: C++14                 
*/
/* LANG can be C++11 or C++14 for those more recent releases */
//http://usaco.org/index.php?page=viewproblem2&cpid=787
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

struct Farmer{
    int max;
    int pay;
};

struct comp {
    bool operator()( Farmer a,Farmer b ) const { 
        return a.pay > b.pay;
    }
};

struct rev {
    bool operator()( int a, int b ) const { 
        return a>b;
    }
};

int  main() {
    //Too difficult, can't solve or understand at all
    ofstream fout ("rental.out");
    ifstream fin ("rental.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> params=split(inputstrings[0]," ");
    vector<int> cows;
    vector<Farmer> farmers;
    vector<int> renters;
    for(int i=0;i<stoi(params[0]);i++){
        cows.push_back(stoi(inputstrings[i+1]));
    }
    for(int i=0;i<stoi(params[1]);i++){
        Farmer farmer=Farmer();
        farmer.max=stoi(split(inputstrings[i+1+stoi(params[0])]," ")[0]);
        farmer.pay=stoi(split(inputstrings[i+1+stoi(params[0])]," ")[1]);
        farmers.push_back(farmer);
    }
    for(int i=0;i<stoi(params[2]);i++){
        renters.push_back(stoi(inputstrings[i+1+stoi(params[0])+stoi(params[1])]));
    }
    sort(farmers.begin(),farmers.end(),comp());
    sort(renters.begin(),renters.end(),rev());
    sort(cows.begin(),cows.end(),rev());
    vector<int> options={0};
    int prevMilked=0;
    for(int i=0;i<cows.size();i++){
        for(int k=0;k<farmers.size();k++){
            if(farmers[k].max>cows[i]){
                farmers[k].max-=cows[i];
                prevMilked+=farmers[k].pay*cows[i];
                cows[i]=0;
                break;
            }else{
                prevMilked+=farmers[k].pay*farmers[k].max;
                cows[i]-=farmers[k].max;
                farmers[k].max=0;
                farmers.erase(farmers.begin()+k);
                k--;
            }
        }
        options.push_back(prevMilked);
    }
    int prevRent=0;
    for(int i=options.size()-2;i>=0;i--){
        if(options.size()-2-i<renters.size()){
            prevRent+=renters[options.size()-2-i];
        }
        options[i]+=prevRent;
    }
    int ans=0;
    for(int i=0;i<options.size();i++){
        ans=max(options[i],ans);
    }
    fout << ans << endl;
    return 0;
}