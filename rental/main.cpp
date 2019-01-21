/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: rental
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

int sumOf(vector<int> inp,int n){
    int ret=0;
    for(int i=0;i<n&&i<inp.size();i++){
        ret+=inp[i];
    }
    return ret;
}

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
    //have a prefix sum for the total, and find the max.
    //loop through each cow.
    int milkedSum=0;
    int ans=0;
    for(int i=0;i<cows.size();i++){
        for(int k=0;k<farmers.size();k++){
            if(farmers[k].max>cows[i]){
                farmers[k].max-=cows[i];
                milkedSum+=cows[i]*farmers[k].pay;
                cows[i]=0;
                break;
            }else{
                cows[i]-=farmers[k].max;
                milkedSum+=farmers[k].max*farmers[k].pay;
                farmers.erase(farmers.begin()+k);
                k--;
            }
        }
        ans=max(ans,milkedSum+sumOf(renters,cows.size()-i-1));
//        cout<<milkedSum+sumOf(renters,cows.size()-i-1)<<endl;
    }

    /*
    for(int i=0;i<cows.size();i++){
        ans=max(ans,milkedSum+sumOf(renters,cows.size()-i));
        for(int k=0;k<farmers.size();k++){
            if(farmers[k].max>=cows[i]){
                milkedSum+=farmers[k].pay*cows[i];
                farmers[k].max-=cows[i];
                break;
            }else{
                milkedSum+=farmers[k].pay*farmers[k].max;
                cows[i]-=farmers[k].max;
                farmers.erase(farmers.begin()+k);
                k--;
            }
        }
    }*/
    fout << ans << endl;
    /*
    for(int i=0;i<cows.size();i++){
        vector<Farmer> clone=farmers;
        int milkLeft=cows[i];
        int milkPrice=0;
        for(int k=0;k<farmers.size();k++){
            if(milkLeft==0){
                break;
            }
            if(farmers[i].max>0){
                if(milkLeft<farmers[k].max){ //still some more left to buy
                    milkPrice+=farmers[k].pay*milkLeft;
                    farmers[k].max-=milkLeft;
                    milkLeft=0;
                }else if(milkLeft>=farmers[k].max){ //still some more left to buy
                    milkPrice+=farmers[k].pay*farmers[k].max;
                    milkLeft-=farmers[k].max;
                    k--;
                }
            }
        }
        int rentPrice=renters.size()>0?renters[0]:0;
        if(rentPrice>milkPrice){
            cout <<  "Rented cow "<<cows[i]<<" for "<<rentPrice<<endl;
            renters.erase(renters.begin());
            farmers=clone;
        }else{
            cout << "Milked cow "<< cows[i] << " for "<<milkPrice << endl;
        }
     //   cout << milkPrice << " " << rentPrice << endl;
    }*/
    return 0;
}