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

int main() {
    ofstream fout("rental.out");
    ifstream fin("rental.in");
    int N,M,R;
    fin >> N >> M >> R;
    vector<int> milk=vector<int>(N);
    priority_queue<Buyer,vector<Buyer>,sortBuyers> buyers;
    priority_queue<int,vector<int>,sortRenters> renters;
    for(int i=0;i<N;i++){
        fin >> milk[i];
    }
    for(int i=0;i<M;i++){
        Buyer buyer=Buyer();
        fin >> buyer.maxAmount >> buyer.cents;
        buyers.emplace(buyer);
    }
    for(int i=0;i<R;i++){
        int a;
        fin >> a;
        renters.emplace(a);
    }
    sort(milk.begin(),milk.end());
    // smallest to largest
    long long profit=0;
    for(auto &cowAmount:milk){
        int profitIfMilked=0;
        Buyer currentBuyer=buyers.top();
        priority_queue<Buyer,vector<Buyer>,sortBuyers> localBuyers=buyers;
        while(cowAmount>0 && currentBuyer.cents>0){
            int amountMilked=min(cowAmount,currentBuyer.maxAmount);
            cout << "Milked " << amountMilked << " because "<<cowAmount<<" and " <<currentBuyer.maxAmount<<endl;
            profitIfMilked+=amountMilked*currentBuyer.cents;
            currentBuyer.maxAmount-=amountMilked;
            cowAmount-=amountMilked;
            if(currentBuyer.maxAmount==0){
                localBuyers.pop();
                currentBuyer=localBuyers.top();
            }
        }
        int profitIfRented=renters.top();
        renters.pop();
        if(profitIfMilked<profitIfRented){
            profit+=profitIfRented;
        }else{
            profit+=profitIfMilked;
        }
    }
    fout << profit << endl;
    return 0;
}