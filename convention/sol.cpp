/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: kento241
TASK: convention
LANG: C++14                 
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <stdio.h> 
#include <string.h> 
#include <typeinfo>
#include <numeric>
#include <algorithm>
#include <cmath>
using namespace std;
 
int N,M,C;
vector<int> t;
 
bool pos(int wait)
{
	int wagons = 1;
	int firstArrival = t[0];
	int firstIndex = 0;
	for(int i=1;i<N;i++)
	{
		if(t[i] - firstArrival > wait || i + 1 - firstIndex > C)
		{
			wagons += 1;
			firstArrival = t[i];
			firstIndex = i;
		}
	}
	return (wagons <= M);
}
 
int binSearch(int low,int high)
{
	if(low == high) return low;
	if(low + 1 == high)
	{
		if(pos(low)) return low;
		return high;
	}
	int mid = (low+high)/2;
	if(pos(mid)) return binSearch(low,mid);
	else return binSearch(mid+1,high);
}
 
vector<string> split(string str, string character){
    vector<string> result;
    int s=0;
    int i=0;
    while(i<str.length()){
        if(str[i]==character[0]||i==str.length()-1){
            int x=i-s;
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

int main()
{	
    ofstream fout ("convention.out");
    ifstream fin ("convention.in");
    vector<string> inputstrings;
    string contents;
    while(getline(fin,contents)) {
        inputstrings.push_back(contents);
    }
	N=stoi(split(inputstrings[0]," ")[0]);
	M=stoi(split(inputstrings[0]," ")[1]);
	C=stoi(split(inputstrings[0]," ")[2]);
	vector<string> splitted=split(inputstrings[1]," ");
	for(int i=0;i<splitted.size();i++){
		t.push_back(stoi(splitted[i]));
	//	cout << t[i] << endl;
	}
	sort(t.begin(),t.end());
	fout << binSearch(0, t[t.size()-1]-t[0]) << '\n';
	return 0;
}