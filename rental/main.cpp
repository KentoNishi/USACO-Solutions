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
    long long quantity;
    long long price;
};

struct comp {
    bool operator()( Shop a, Shop b ) const { 
        return a.price > b.price;
    }
};

struct rev {
    bool operator()( long long a,long long b ) const { 
        return a>b;
    }
};

int main() {
    ofstream fout ("rental.out");
    ifstream fin ("rental.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
    vector<string> firstLine=split(inputstrings[0]," ");
    vector<long long> cows;
    for(long long i=1;i<=stoi(firstLine[0]);i++){
        cows.push_back(stoi(inputstrings[i]));
    }
    sort(cows.begin(),cows.end(),rev());
    vector<Shop> shops;
    for(long long i=stoi(firstLine[0])+1;i<1+stoi(firstLine[0])+stoi(firstLine[1]);i++){
        vector<string> line=split(inputstrings[i]," ");
        Shop shop=Shop();
        shop.price=(stoi(line[1]));
        shop.quantity=(stoi(line[0]));
        shops.push_back(shop);
    }
    sort(shops.begin(),shops.end(),comp());
    vector<long long> maxProfit;
    for(long long i=0;i<stoi(firstLine[0])+1;i++){
        maxProfit.push_back(0);
    }
    long long index=0;
    for(long long i=0;i<stoi(firstLine[0]);i++){
        maxProfit[i+1]=maxProfit[i];
        while(index<stoi(firstLine[1])&&cows[i]>0){
            long long use=min(cows[i],shops[index].quantity);
            maxProfit[i+1]+=use*shops[index].price;
            cows[i]-=use;
            shops[index].quantity-=use;
            if(shops[index].quantity==0){
                index++;
            }
        }
    }
    vector<long long> rental;
    for(long long i=stoi(firstLine[0])+stoi(firstLine[1])+1;i<stoi(firstLine[0])+stoi(firstLine[1])+stoi(firstLine[2])+1;i++){
        rental.push_back(stoi(inputstrings[i]));
    }
    sort(rental.begin(),rental.end(),rev());
    long long revRent=0;
    long long prev=0;
    for(long long i=stoi(firstLine[0])-1;i>=0&&revRent<stoi(firstLine[2]);i--){
        prev+=rental[revRent];
        maxProfit[i]+=prev;
        revRent++;
    }
    long long ans=0;
    for(long long i=0;i<maxProfit.size();i++){
        ans=max(ans,maxProfit[i]);
    }
    fout << ans << endl;
    return 0;
}