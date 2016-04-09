#include <iostream>
#include <bits/stdc++.h>
#include <vector>
using namespace std;


// -------------------- interface .h -----------------------------------
//galpao
class Galpao
{
private:
	int sum;
	vector<int> vec;

public:
	Galpao();
	~Galpao();
	int getNumItens();
	void add(int w);

};


// caminhao
class Caminhao
{
private:
	int capacity, sum;
	vector<int> vec;
public:
	Caminhao();
	~Caminhao();
	void loa(Galpao g);
	
};

// ------------------ implementacao .cpp --------------------------
//galpao
Galpao::Galpao(){
	sum = 0;
}

Galpao::~Galpao(){}

int Galpao::getNumItens(){
	return vec.size();
}
void Galpao::add(int w){
	sum += w;
	vec.push_back(w);
	cout << vec.size() << " " << sum << endl;
}

//caminhao
Caminhao::Caminhao(){
	capacity = 0;
	sum = 0;
};
Caminhao::~Caminhao(){};
void Caminhao::loa(Galpao g){
	cout << "ae" << endl;
}
// ------------------------ main .cpp ------------------------------

int main(){

	Galpao g;
	g.add(10);
	g.add(2);
	int i;
	cin >> i;
	Caminhao *c = new Caminhao[i];
	for(int j = 0; j < i; j++){
		c[j].loa(g);
	}
	return 0;
}