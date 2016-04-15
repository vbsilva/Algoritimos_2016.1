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
	queue<int> getQueue();
	void printQueue();
	int getSum();
	void pushQueue(int w);
	void adcSum(int w);
	int decSum(int w);
	int getSize();
	bool isEmpty();
	int nextQ();
	void removeNext();
	void zeraSatanai();
	void add(int w);

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
	void zeraMisera();
	int getSum();
	
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

int Galpao::getSize(){ return this->q.size(); }

bool Galpao::isEmpty(){ return this->q.empty(); }

int Galpao::nextQ(){ return this->q.front(); }

void Galpao::removeNext(){ this->q.pop(); }

queue<int> Galpao::getQueue(){ return this->q; }

int Galpao::getSum(){ return this->sum; }

void Galpao::adcSum(int w){
	this->sum += w;
}

void Galpao::pushQueue(int w){
	this->q.push(w);
}

int Galpao::decSum(int w){
	this->sum -= w;
}

void Galpao::zeraSatanai(){
	this->sum = 0;
	while(!this->q.empty()) this->q.pop();
}

void Galpao::add(int w){
	//cout << " ADDantes: " << this->sum << " " << this->q.size() << endl;
	this->sum += w;
	this->q.push(w);
	cout << this->q.size() << " " << this->sum << endl;
}

//caminhao
Caminhao::Caminhao(){
	this->capacity = 0;
	this->sum = 0;
	while(!this->s.empty()) this->s.pop();
}

Caminhao::~Caminhao(){ }

void Caminhao::printStack(){
	stack<int> temp = this->s;
	cout<< "caminhao: ";
	while(!temp.empty()){
		cout << temp.top() << " ";
		temp.pop();
	}
	cout << endl;
}
void Caminhao::zeraMisera(){
	this->sum = 0;
	this->capacity = 0;
	while(!this->s.empty()) this->s.pop();

}
void Caminhao::loa(Galpao &g){
	//cout << " LOAantes: " << "total: " << this->sum << "itens: " << this->s.size() << "cap: " << this->capacity  << endl;
	while(!g.isEmpty() && g.nextQ() + this->sum <= this->capacity){
		int temp = g.nextQ();
		g.removeNext();
		g.decSum(temp);
		this->s.push(temp);
		this->sum += temp;
	}

	cout << " " << this->s.size() << endl;
}

void Caminhao::del(){
	if(this->s.size() > 0){
		this->sum -= this->s.top();
		this->s.pop();
	}
	cout << this->s.size() << endl;
}

void Caminhao::inf(){
	cout << this->s.size() << " " << this->sum << endl;
}

void Caminhao::setCapacity(int c){
	this->capacity = c;
}

int Caminhao::getCapacity(){ return this->capacity; }

int Caminhao::getSize(){ return this->s.size(); }
int Caminhao::getSum(){ return this->sum; }
// ------------------------ main .cpp ------------------------------

int main(){

	bool newCase = false, firstTime = true, end = false, x = true;
	int n, cap, op, m, v;
	char str[4];
	Galpao g;
	while(!end){
		if(firstTime) scanf("%d", &n);
		Caminhao *c = new Caminhao[n];
		for(int j = 0; j < n; j++){
			scanf(" %d", &cap);
			c[j].setCapacity(cap);
			//cout << "capacidade "<< j << " " << cap << endl;
		}
		firstTime = false;
		while(true){
			if(scanf("%s", str) == EOF){
				end = true;
				break;
			}
			if(!strcmp(str, "ADD")){
				scanf("%d", &op);
				g.add(op);

			}else if(!strcmp(str, "LOA")){
				scanf("%d", &op);
				cout << op;
				c[op].loa(g);
				//cout << "depois: total: " << c[op].getSum() << " itens: " << c[op].getSize() << endl;
				
			}else if(!strcmp(str, "DEL")){
				scanf("%d", &op);
				cout << op << " ";
				c[op].del();
				
			}else if(!strcmp(str, "INF")){
				scanf("%d", &op);
				cout << op << " ";
				c[op].inf();

			}else{
				n = atoi(str);
				cout << endl;
				delete [] c;
				c = NULL;
				g.zeraSatanai();
				break;
			}

		}
	}
	

	return 0;
}
