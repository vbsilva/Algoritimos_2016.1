#include <string>

class MyClass
{
private:
	int val;
	std::string nome;
public:
	MyClass();
	~MyClass();
	void setVal(int v);
	int getVal();
	void setNome(std::string n);
	std::string getNome();
	
};