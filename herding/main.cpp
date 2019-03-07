#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <bitset>
#include <tuple>
#include <cmath>
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

int sumOf(vector<int> arr){
    int res=0;
    for(int i=0;i<arr.size();i++){
        res+=arr[i];
    }
    return res;
}

vector<int> cows;

int best(){
    if(cows[cows.size()-2]-cows[0]==cows.size()-2&&cows[cows.size()-1]-cows[cows.size()-2]>2){
        return 2;
    }
    if(cows[cows.size()-1]-cows[1]==cows.size()-2&&cows[1]-cows[0]>2){
        return 2;
    }
    int j=1;
    int ans=0;
    for(int i=0;i<cows.size();i++){
        j=i+1;
        while(j<cows.size()&&cows[j]-cows[i]<cows.size()){
            j++;
        }
        ans=max(ans,j-i);
    }
    return cows.size()-ans;
}

int main() {
    ofstream fout ("herding.out");
    ifstream fin ("herding.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
	for (int i = 1; i < inputstrings.size();i++){
        cows.push_back(stoi(inputstrings[i]));
	}
	sort(cows.begin(), cows.end());
    int ans1=best();
    int ans2=max(cows[cows.size()-2]-cows[0],cows[cows.size()-1]-cows[1])-(cows.size()-2);
    fout << ans1 <<endl<<ans2<< endl;
	return 0;
}