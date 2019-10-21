// rental - Silver - January 2017-2018 - http://usaco.org/index.php?page=viewproblem2&cpid=787

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <queue>
using namespace std;

struct Buyer{
    int maxAmount;
    int cents;
    Buyer(int m, int c){
        maxAmount=m;
        cents=c;
    }
    Buyer(){

    }
};

struct sortBuyers {
    bool operator()(Buyer a, Buyer b) const { 
        return a.cents > b.cents;
    }
};

struct sortRenters {
    bool operator()(int a, int b) const { 
        return a>b;
    }
};

struct sortMilk {
    bool operator()(int a, int b) const { 
        return a<b;
    }
};

int main() {
    ofstream fout("rental.out");
    ifstream fin("rental.in");
    int N,M,R;
    fin >> N >> M >> R;
    vector<int> milk=vector<int>(N);
    vector<Buyer> buyers=vector<Buyer>(M);
    vector<int> renters=vector<int>(R);
    for(int i=0;i<N;i++){
        fin >> milk[i];
    }
    for(int i=0;i<M;i++){
        Buyer buyer=Buyer();
        fin >> buyer.maxAmount >> buyer.cents;
        buyers[i]=buyer;
    }
    for(int i=0;i<R;i++){
        int a;
        fin >> a;
        renters[i]=a;
    }
    sort(milk.begin(),milk.end(),sortMilk());
    sort(buyers.begin(),buyers.end(),sortBuyers());
    sort(renters.begin(),renters.end(),sortRenters());
    // milk: least to most
    // buyers: highest to lowest
    // renters: highest to lowest
    // rent out lowest, milk highest
    vector<long long> profits(N,0);
    // profits if renting first X cows starting from 0
    profits[1]=renters[0];
    for(int i=2;i<N && i<R+1;i++){
        profits[i]=profits[i-1]+renters[i-1];
    }
    // add the profits for milking the last N-X cows
    int buyerIndex=0;
    int profitFromMilking=0;
    for(int i=N-1;i>=0;i--){
        profits[i]+=profitFromMilking;
        while(buyerIndex<M && milk[i]>0){
            int amountMilked=min(milk[i],buyers[buyerIndex].maxAmount);
            milk[i]-=amountMilked;
            buyers[buyerIndex].maxAmount-=amountMilked;
            profits[i]+=buyers[buyerIndex].cents*amountMilked;
            profitFromMilking+=buyers[buyerIndex].cents*amountMilked;
            if(buyers[buyerIndex].maxAmount==0){
                buyerIndex++;
            }
        }
    }
    long long maximum=0;
    for(int i=0;i<profits.size();i++){
        maximum=max(profits[i],maximum);
    }
    fout << maximum << endl;
    return 0;
}