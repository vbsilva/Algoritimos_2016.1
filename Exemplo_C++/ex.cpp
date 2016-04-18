#include "ex.h"
#include <string>
#include <iostream>
using namespace std;


MyClass::MyClass(){}

MyClass::~MyClass(){}

void MyClass::setVal(int v){
	this->val = v;
}

int MyClass::getVal(){ return this->val; }

void MyClass::setNome(string s){
	this->nome = s;
}

string MyClass::getNome(){ return this->nome; }


int main(){

	MyClass A;
	A.setNome("ola mundo!");
	cout << A.getNome() << endl;
}