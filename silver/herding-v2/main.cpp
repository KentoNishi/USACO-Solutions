//http://usaco.org/index.php?page=viewproblem2&cpid=918
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

vector<int> cows;

int best(){
    if(cows[cows.size()-2]-cows[0]==cows.size()-2&&cows[cows.size()-1]-cows[cows.size()-2]>2){
        return 2;
    }
    if(cows[cows.size()-1]-cows[1]==cows.size()-2&&cows[1]-cows[0]>2){
        return 2;
    }
    int ans=INFINITY;
    for(int i=0;i<cows.size();i++){
        int j=i+1;
        while(j<cows.size()&&cows[j]-cows[i]<cows.size()){
            j++;
        }
//        cout << cows.size() << " " << i << " " << j << " = " << int(cows.size())-(j-i) << endl;
        ans=min(ans,int(cows.size())-(j-i));
    }
    return ans;
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