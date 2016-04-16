#include <bits/stdc++.h>
#include <iterator>
using namespace std;

// interface .h
class bolas
{
private:
	int *val;
public:
	bolas();
	~bolas();
	void init(int v);
	void setVal(int v, int w);
	int getVal(int v);
	void sort();
	
};



class jogador
{
private:
	int *val;
public:
	jogador();
	~jogador();
	void init(int w);
	int getScore(bolas b, int k);
	
};


// implementação .cpp

bolas::bolas(){}

bolas::~bolas(){}

void bolas::init(int w){
	this->val = (int *)calloc(w, sizeof(int));
}

void bolas::setVal(int pos, int v){
	this->val[pos] = v;
}

int bolas::getVal(int pos){ return this->val[pos]; }

void bolas::sort(){
	std::sort(this->val, (this->val) + 10);	
}




jogador::jogador(){}

jogador::~jogador(){}

void jogador::init(int w){
	this->val = (int *)calloc(w, sizeof(int));
}

int jogador::getScore(bolas b, int k){
	for (int i = 0; i < k; ++i){
		/* code */
	}
}
// source.cpp 

int main(){

	bolas b;
	int n, m, k, p, a, v;

	while( scanf("%d %d %d %d %d", &n, &m, &k, &p, &a) != EOF){
		b.init(n);
		for (int i = 0; i < n; ++i){
			cin >> v;
			b.setVal(i, v);
			cout << "bola " << i << ": " << b.getVal(i) << endl;
		}
		for (int i = 0; i < p; ++i){
			for (int j = 0; j < k; ++j){
				
			}
		}
		b.sort();
		cout << endl;
		for (int i = 0; i < n; ++i){
			cout << "bola " << i << ": " << b.getVal(i) << endl;
		}

	}

	return 0;
}

