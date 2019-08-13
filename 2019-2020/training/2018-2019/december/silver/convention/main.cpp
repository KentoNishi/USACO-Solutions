// convention - Silver - December 2018-2019 - http://usaco.org/index.php?page=viewproblem2&cpid=858

/*
    Summary:
        Find the longest time a cow has to wait in an optimally distributed arrangement.
    Solution: 
        Binary search through the possible wait times, and check if it's possible.
            If possible:
                Set the minimum maximum time
            If not possible:
                Continue the search    
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <array>
using namespace std;

int main() {
    ofstream fout ("convention.out");
    ifstream fin ("convention.in");
    long long N,M,C;
    /*
        N: # of cows arriving
        M: # of buses
        C: # of seats on each bus
    */
    fin >> N >> M >> C;
    vector<long long> cows=vector<long long>(N);
    for(long long i=0;i<N;i++){
        fin >> cows[i];
    }
    sort(cows.begin(),cows.end());
    long long shortestMaximumWait=cows.back()-cows.front();
    long long lowerBound=0;
    long long higherBound=shortestMaximumWait;
    while(higherBound-lowerBound>1){
        long long trialTime=(lowerBound+higherBound)/2;
        long long currentCow=0;
        for(long long i=0;i<M;i++){ // for each bus
            long long firstCow=currentCow;
            if(currentCow<N-1){
                currentCow++;
            }
            while( currentCow<N && (cows[currentCow]-cows[firstCow]<=trialTime && 
                    currentCow-firstCow+1<=C )){
                /*
                    while the wait time is not above the trial time and
                    while the number of cows in the bus is below the max
                */
                currentCow++;
            }
        }
        if(currentCow==N){
            // all the cows went on the bus
            higherBound=trialTime;
            shortestMaximumWait=trialTime;
        }else{
            // not all the cows made it
            lowerBound=trialTime;
        }
    }
    fout << shortestMaximumWait << endl;
    return 0;
}
