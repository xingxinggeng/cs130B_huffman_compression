#include <stdio.h>
#include <algorithm>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>  
#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <sstream> 

using namespace std;

ofstream myfile ("codewords.txt");

struct Node{
	Node* left;
	Node* right;
	int frequency;
	int character;
	Node(int c, int f, Node* l, Node* r){
		character=c;
		frequency=f;
		left=l;
		right=r;
	}
};


struct myComparator{
public:
	bool operator()(Node* p1,  Node* p2){
		return p1->frequency > p2->frequency;
	}
};

void output_huff_code(Node* root, string str){
	if(!root)
		return;
	if(root->character != -1){
		myfile << to_string(root->character) <<"	"<< str<< endl;
		//sizeCount=sizeCount+str.size()* (root->frequency);
	}
	output_huff_code(root->left, str+"0");
	output_huff_code(root->right,str+"1");
}

int fileSize( Node* root,int length){
	//TODO
	int count=0;
	if(!root)
		return 0;
	if(root->character != -1){
		count = count+ root->frequency * length;
	}

	return count + fileSize(root->left,length+1) + fileSize(root->right,length+1);
}




int main(){
	string s;
	priority_queue <Node*,vector<Node*>,myComparator> pq;
	while(getline(cin,s)){
		istringstream iss (s);
		int asc;
		iss >> asc;
		int fre;
		iss>> fre;
		/*
		string ascii;
		int i=0;
		for(i=0; i<s.size(); i++){
			if(s[i]==' ')
				break;
			ascii=ascii+ s[i];

		}
		string freq;
		for(int j=i; j<s.size();j++){
			if(s[j]!=' '){
				freq=freq+s[j];
			}
		}
		int asc= stoi(ascii);
		int fre= stoi(freq);
		*/
		pq.push(new Node(asc,fre,0,0));
	
	}

	Node* top =0;
	Node* left=0;
	Node* right=0;

	while (pq.size() != 1) {
        left = pq.top();
        pq.pop();
        right = pq.top();
        pq.pop();
        
        top = new Node(-1, left->frequency + right->frequency, 0, 0);
 
        top->left = left;
        top->right = right;
 
        pq.push(top);
    }
    
    output_huff_code(pq.top(),"");
    myfile.close();
    cout << to_string(fileSize(pq.top(),0))<<endl;


}