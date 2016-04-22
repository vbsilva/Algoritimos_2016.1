#include <bits/stdc++.h>
//#include <boost/algorithm/string.hpp>
using namespace std;

int main(){
	string str;
	//vector<string> SplitVec;
	getline(cin, str);
	if(str == "$TEXTO"){
		while(str != "$CONSULTAS"){
			getline(cin, str);
			//boost::split(SplitVec, str, boost::is_any_of(" "));
		}
	}
	return 0;
}