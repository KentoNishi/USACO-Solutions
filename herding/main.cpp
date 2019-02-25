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
    int prev=cows[0];
    vector<int> gaps;
    for(int i=1;i<cows.size();i++){
        if(cows[i]-prev-1>0){
            gaps.push_back(cows[i]-prev-1);
        }
        prev=cows[i];
    }
    int ans1=-1;
    int ans2=-1;
    sort(gaps.begin(),gaps.end(),greater<int>());
    if(gaps.size()!=0){
        if(cows.size()==3){
            if(cows[2]-cows[1]==2||cows[1]-cows[0]==2){
                ans1=1;
            }else{
                ans1=2;
            }
        }else{
            ans1=(float(sumOf(gaps)-min(gaps[0],gaps[gaps.size()-1]))/2)+1;
        }
        ans2=sumOf(gaps)-min(gaps[0],gaps[gaps.size()-1]);
    }else{
        ans1=0;
        ans2=0;
    }

    fout << ans1 <<endl<<ans2<< endl;
	return 0;
}