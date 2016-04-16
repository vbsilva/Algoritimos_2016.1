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
	void sort(int n);
	
};



class jogador
{
private:
	int score;
public:
	jogador();
	~jogador();
	int setScore(int n, int k, bolas b);
	int getScore();
	void addScore(int w);
	
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

void bolas::sort(int n){
	std::sort(this->val, (this->val) + n);	
}




jogador::jogador(){}

jogador::~jogador(){}

void jogador::addScore(int w){
	this->score += w;
}

int jogador::getScore(){ return this->score; }

int jogador::setScore(int n, int v, bolas b){
	int l,m,r;
	r = n-1; l = 0; m = r+l/2;


	while(l <= r){
		m = (r+l)/2;
		if(v == b.getVal(m)){
			return m;
		}else if(v < b.getVal(m)){
			r = m-1;
		}else if(v > b.getVal(m)){
			l = m+1;
		}
	}
}
// source.cpp 

int main(){

	bolas b;
	jogador *j;
	int n, m, k, p, a, v, caso = 0;

	while( scanf("%d %d %d %d %d", &n, &m, &k, &p, &a) != EOF){
		cout << "caso " << caso << ":";
		b.init(n);
		for (int i = 0; i < n; ++i){
			cin >> v;
			b.setVal(i, v);
			//cout << "bola " << i << ": " << b.getVal(i) << endl;
		}
		b.sort(n);
		j = new jogador[p];

		for (int i = 0; i < p; ++i){
			for (int t = 0; t < k; ++t){
				cin >> v;
				j[i].addScore(j[i].setScore(n, v, b));
			}
			if(j[i].getScore() == a) cout << " " << i;
		}
	++caso;
	cout << endl << endl;
	}

	return 0;
}

