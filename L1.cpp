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
	void setCapacity(int c);
	int getCapacity();
	
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
}

Caminhao::~Caminhao(){};

void Caminhao::loa(Galpao g){
	cout << "ae" << endl;
}

void Caminhao::setCapacity(int c){
	capacity = c;
}

int Caminhao::getCapacity(){ return capacity; }
// ------------------------ main .cpp ------------------------------

int main(){

	Galpao g;
	bool newCase = 0;
	int n, cap, op;
	char str[4];
	while(!newCase){
		cin >> n;
		Caminhao *c = new Caminhao[n];
		for(int j = 0; j < n; j++){
			cin >> cap;
			c[j].setCapacity(cap);
		}

		while(!newCase){
			cout<< "manda\n";
			cin >> str >> op;
			cout << str << " e " << op << endl;
			cout<< str[0] << endl;
			if(str == "ADD"){
				g.add(op);
				cout << "vixxxx";
			}else if(str == "LOA"){

			}else if(str == "DEL"){

			}else if(str == "INF"){

			}else if(str[0] == '\n'){
				cout << "qqqqq";

			}

		}
	}
	

	return 0;
}