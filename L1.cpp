#include <bits/stdc++.h>
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
	int getSize();
	bool isEmpty();
	int nextQ();
	void removeNext();

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
	void loa(Galpao &g);
	void setCapacity(int c);
	int getCapacity();
	void printStack();
	int getSize();
	void del();
	void inf();
	
};

// ------------------ implementacao .cpp --------------------------
//galpao
Galpao::Galpao(){
	this->sum = 0;
	while(!this->q.empty()) this->q.pop();
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

int Galpao::getSize(){ return q.size(); }

bool Galpao::isEmpty(){ return q.empty(); }

void Galpao::add(int w){
	sum += w;
	q.push(w);
	cout << q.size() << " " << sum << endl;
}

int Galpao::nextQ(){ return q.front(); }
void Galpao::removeNext(){ q.pop(); }

queue<int> Galpao::getQueue(){ return q; }

int Galpao::getSum(){ return sum; }

int Galpao::decSum(int w){
	this->sum -= w;
}

//caminhao
Caminhao::Caminhao(){
	this->capacity = 0;
	this->sum = 0;
	while(!this->s.empty()) this->s.pop();
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

void Caminhao::loa(Galpao &g){
	int temp = g.nextQ();
	while(!g.isEmpty() && this->sum + temp <= this->capacity){
		this->s.push(temp);
		g.removeNext();
		g.decSum(temp);
		this->sum += temp;
		if(!g.isEmpty()) temp = g.nextQ();
	}
	//g.printQueue();
}

void Caminhao::del(){
	if(this->s.size() > 0){
		this->sum -= this->s.top();
		this->s.pop();
	}
	cout << s.size() << endl;
}

void Caminhao::inf(){
	cout << this->s.size() << " " << this->sum << endl;
}

void Caminhao::setCapacity(int c){
	capacity = c;
}

int Caminhao::getCapacity(){ return capacity; }

int Caminhao::getSize(){ return s.size(); }
// ------------------------ main .cpp ------------------------------

int main(){

	bool newCase = false, firstTime = true, end = false;
	int n, cap, op;
	char str[4];
	while(!end){
		if(firstTime){cin >> n;}
		Galpao g;
		Caminhao *c = new Caminhao[n];
		for(int j = 0; j < n; j++){
			cin >> cap;
			c[j].setCapacity(cap);
		}
		firstTime = false;
		while(true){
			if(scanf("%s", str) == EOF){
				end = true;
				break;
			}
			scanf("%d", &op);
			//cout << str << " " << op << endl;
			if(!strcmp(str, "ADD")){
				g.add(op);
			}else if(!strcmp(str, "LOA")){
				if(op>=n){
				}else{
					c[op].loa(g);
					cout << op << " " << c[op].getSize() << endl;
				}
			}else if(!strcmp(str, "DEL")){
				if(op>=n){
				}else{
					cout << op << " ";
					c[op].del();				
				}
			}else if(!strcmp(str, "INF")){
				if(op>=n){
					cout <<"debug: "<< op << " " << n << endl;
				}else{
					cout << op << " ";
					c[op].inf();
				}
			}else{
				n = atoi(str);
				cout << endl;
				//delete[] c; 
				//g.~Galpao();
				break;
			}

		}
	}
	

	return 0;
}