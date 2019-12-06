// Test case path: [path]
// div7 - Silver - January 2015-2019
// http://usaco.org/index.php?page=viewproblem2&cpid=595

#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("div7.in");
    ofstream fout("div7.out");
    int N;
    fin >> N;
    vector<int> original=vector<int>(7,0);
    for(int i=0;i<N;i++){
        int a;
        fin >> a;
        a--;
        original[a]++;
    }
    long long biggestDivisibleCount=0;
    long long biggestDivisible=0;
    long long biggestCount=0;
    long long biggest=0;
    for(int firstChoice=0;firstChoice<7;firstChoice++){
        vector<int> counts=original;
        long long sum=firstChoice+1;
        int nextNumber=7-(sum%7);
        long long count=1;
        while(nextNumber==0||counts[nextNumber-1]>=0){
            if(nextNumber)
            sum+=nextNumber;
            counts[nextNumber-1]--;
            nextNumber=7-(sum%7);
            count++;
        }
        biggest=max(biggest,sum);
        biggestCount=max(biggestCount,count);
        if(sum%7==0){
            biggestDivisible+=sum;
            biggestDivisibleCount+=count;
        }
    }
    fout << max(biggestCount,biggestDivisibleCount) << endl;
    return 0;
}