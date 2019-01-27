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

struct Shop{
    int quantity;
    int price;
};

struct comp {
    bool operator()( Shop a, Shop b ) const { 
        return a.price > b.price;
    }
};

struct rev {
    bool operator()( int a,int b ) const { 
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
    vector<string> firstLine=split(inputstrings[0]," ");
    vector<int> milkProduced;
    for(int i=1;i<=stoi(firstLine[0]);i++){
        milkProduced.push_back(stoi(inputstrings[i]));
    }
    sort(milkProduced.begin(),milkProduced.end(),rev());
    vector<Shop> shops;
    for(int i=stoi(firstLine[0])+1;i<1+stoi(firstLine[0])+stoi(firstLine[1]);i++){
        vector<string> line=split(inputstrings[i]," ");
        Shop shop=Shop();
        shop.price=(stoi(line[1]));
        shop.quantity=(stoi(line[0]));
        shops.push_back(shop);
    }
    sort(shops.begin(),shops.end(),comp());
    vector<int> maxProfit;
    for(int i=0;i<stoi(firstLine[0]);i++){
        //continue
    }
    vector<int> rental;
    for(int i=stoi(firstLine[0])+stoi(firstLine[1])+1;i<stoi(firstLine[0])+stoi(firstLine[1])+stoi(firstLine[2])+1;i++){
        rental.push_back(stoi(inputstrings[i]));
    }
    sort(rental.begin(),rental.end(),rev());
    for(int i=0;i<stoi(firstLine[0])+1;i++){
        maxProfit.push_back(0);
    }
    
    /*
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
    for(int i=0;i<scenarios.size();i++){
        cout << scenarios[i] << endl;
    }*/
    return 0;
}