#include <bits/stdc++.h>
using namespace std;

class wordNode
{
private:
	string word;
	int hashcode;
	vector<int> ocurrences;
public:
	wordNode(char *word);
	~wordNode();
	string getWord();
	void setHashcode();
	int getHashcode();

	
};
string wordNode::getWord(){ return this->word; }

void wordNode::setHashcode(){
	int x = this->word.length();
	for (int i = 1; i <= x; ++i){
		this->hashcode += (this->word.at(i-1) - 'a')*(pow(26, x-i));
	}
	cout << this->hashcode << endl;
}

int wordNode::getHashcode(){ return this->hashcode; }

wordNode::wordNode(char *word){
	this->word = word;
	this->setHashcode();
	//this->hashcode = this->setHashcode()
}


int main(){
	char line[100];
	char *token;

	scanf("%[^\n]", line);

	if(!(strcmp(line, "$TEXTO"))){
		while(true){
			scanf(" %[^\n]", line);
			token = strtok(line, " ");
			while(token != NULL){
				cout << token << endl;;
				wordNode *w = new wordNode(token);
				token = strtok(NULL, " ");
			}
			break;

		}
	}
return 0;
}
