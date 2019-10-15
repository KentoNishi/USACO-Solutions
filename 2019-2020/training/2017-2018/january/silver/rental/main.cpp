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
        return a>b;
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
    long long profit=0;
    int buyerIndex=0;
    int renterIndex=0;
    for(auto &milkAmount:milk){
        int profitIfRented=renterIndex<R?renters[renterIndex]:0;
        int profitIfMilked=0;
        vector<Buyer> buyerClone=buyers;
        int currentBuyer=buyerIndex;
        while(milkAmount>0 && currentBuyer<M){
            int amountMilked=min(milkAmount,buyerClone[currentBuyer].maxAmount);
            profitIfMilked+=amountMilked*buyerClone[currentBuyer].cents;
            buyerClone[currentBuyer].maxAmount-=amountMilked;
            milkAmount-=amountMilked;
            if(buyerClone[currentBuyer].maxAmount<=0){
                currentBuyer++;
            }
        }
        if(profitIfRented>profitIfMilked){
            profit+=profitIfRented;
            renterIndex++;
        }else{
            profit+=profitIfMilked;
            buyerIndex=currentBuyer;
        }
    }
    fout << profit << endl;
    return 0;
}