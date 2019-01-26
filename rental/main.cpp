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
    vector<int> scenarios;
    int prev=0;
    for(int i=-1;i==-1||i<cows.size();i++){
        scenarios.push_back(prev);
        if(i!=-1){
            int amount=cows[i];
            int moneyMilked=0;
            for(int k=0;k<farmers.size();k++){
                if(amount>farmers[k].max){
                    moneyMilked+=farmers[k].max*farmers[k].pay;
                    farmers[k].max=0;
                    amount-=farmers[k].max;
                    farmers.erase(farmers.begin()+k);
                    k--;
                }else{
                    moneyMilked+=farmers[k].pay*amount;
                    amount=0;
                    farmers[k].max-=amount;
                    break;
                }
            }
            prev+=moneyMilked;
            scenarios[scenarios.size()-1]=prev;
        }
    }
    for(int i=0;i<scenarios.size();i++){
        cout << scenarios[i] << endl;
    }
    return 0;
}