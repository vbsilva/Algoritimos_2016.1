//#include <iostream>
#include <bits/stdc++.h>
//#include <vector>
using namespace std;


// -------------------- interface .h -----------------------------------
//galpao
class Galpao
{
private:
	int sum;
	queue<int> q;

public:
	Galpao();
	~Galpao();
	void add(int w);
	queue<int> getQueue();
	void printQueue();
	int getSum();
	int decSum(int w);

};


// caminhao
class Caminhao
{
private:
	int capacity, sum;
	stack<int> s;
public:
	Caminhao();
	~Caminhao();
	void loa(Galpao g);
	void setCapacity(int c);
	int getCapacity();
	void printStack();
	
};

// ------------------ implementacao .cpp --------------------------
//galpao
Galpao::Galpao(){
	sum = 0;
}

Galpao::~Galpao(){}


void Galpao::printQueue(){
	queue<int> temp = this->q;
	cout<< "galpao: ";
	while(!temp.empty()){
		cout << temp.front() << " ";
		temp.pop();
	}
	cout << endl;
}

void Galpao::add(int w){
	sum += w;
	q.push(w);
	cout << q.size() << " " << sum << endl;
}

queue<int> Galpao::getQueue(){ return q; }

int Galpao::getSum(){ return sum; }

int Galpao::decSum(int w){
	this->sum -= w;
	cout << "total galpao: " << this->sum << endl;
}

//caminhao
Caminhao::Caminhao(){
	capacity = 0;
	sum = 0;
}

Caminhao::~Caminhao(){};

void Caminhao::printStack(){
	stack<int> temp = this->s;
	cout<< "caminhao: ";
	while(!temp.empty()){
		cout << temp.top() << " ";
		temp.pop();
	}
	cout << endl;
}

void Caminhao::loa(Galpao g){
	queue<int> q = g.getQueue();
	int temp = g.getQueue().front();
	while(!q.empty() && this->sum + temp <= this->capacity){
		this->s.push(temp);
		this->sum += temp;
		q.pop();
		g.decSum(temp);
		temp = q.front();
	}
	g.printQueue();

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

		while(true){
			newCase = true;
			cin >> str >> op;
			if(!strcmp(str, "ADD")){
				g.add(op);
			}else if(!strcmp(str, "LOA")){
				c[op].loa(g);
				c[op].printStack();
				cout << "debug " << g.getSum() << endl;
			}else if(str == "DEL"){

			}else if(str == "INF"){

			}else if(str[0] == '\n'){
				cout << "qqqqq";

			}

		}
	}
	

	return 0;
}