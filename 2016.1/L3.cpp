#include <bits/stdc++.h>
using namespace std;

class wordNode
{
private:
	string word;
	int hashcode;
	vector<int> ocurrences;

public:
	wordNode(char *, int);
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
}

int wordNode::getHashcode(){ return this->hashcode; }

wordNode::wordNode(char *word, int i){
	this->word = word;
	this->setHashcode();
	this->ocurrences.push_back(i);
	cout << this->hashcode << " ";
	for (int i = 0; i < this->ocurrences.size(); ++i){
		cout << " " << ocurrences[i];
	}
	cout << endl;
}


int main(){
	char line[100], *token;
	int i;

	scanf("%[^\n]", line);

	if(!(strcmp(line, "$TEXTO"))){
		i = 0;
		while(true){
			scanf(" %[^\n]", line);
			++i;
			token = strtok(line, " ");
			while(token != NULL){
				cout << token << endl;;
				wordNode *w = new wordNode(token, i);
				token = strtok(NULL, " ");
			}
			break;

		}
	}
return 0;
}

