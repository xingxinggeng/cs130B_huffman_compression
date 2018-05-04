//issues to be solved
//1.line 27, usage of compare in priority_queue
//2.set the format of the string in the output file

#include <iostream>
#include <iterator>
#include <string>
#include <fstream>
#include <cstdlib>
#include <queue>
#include <vector>
#include <sstream>

using namespace std;

struct Node{
		int character;
		int frequency;
		Node *left;
		Node *right;
		Node(int data, int freq){
				character  = data;
				frequency = freq;
				left = right = NULL;
		}
};

struct compare{
		bool operator()(Node* lt, Node* rt){
				return (lt->frequency > rt->frequency);
		}
};


//traverse huffman tree
void printHuffmanCode(Node* root,string wordCode,ofstream& outfile,int& compressionSize){
        if( !root ) 
				return;
        if(root->character != int('#') ){
				char buffer[100];
				sprintf(buffer, "%-5d \t %s", root->character, wordCode.c_str());
			//	sprintf(buffer, "%-5d \t %c \t %s", root->character,char( root->character), wordCode.c_str());
				outfile << buffer << endl;
				//outfile<<("%-5d\t%s \n",root->character, wordCode);	
				//outfile<<root->character<<"    "<<wordCode<<endl;
				compressionSize += root->frequency * wordCode.length();
        }

        printHuffmanCode(root->left,wordCode + "0",outfile, compressionSize);
		printHuffmanCode(root->right,wordCode + "1",outfile, compressionSize);
}

//construct huffman tree
void constructHuffmanCode(vector<int> data,vector<int> freq, int size){
		struct Node *lt, *rt, *top;
		int compressionSize = 0;
		ofstream out;
		out.open("codewords.txt");
		std::priority_queue<Node*,vector<Node*>,compare> minHeap;

		for(int i = 0; i<size; i++){
				minHeap.push(new Node(data[i],freq[i]));
		}

		while(minHeap.size() != 1){
				lt = minHeap.top();
				minHeap.pop();

				rt = minHeap.top();
				minHeap.pop();

				top = new Node( int('#'), lt->frequency + rt->frequency);
				top->left = lt;
				top->right = rt;

				minHeap.push(top);
		}
		printHuffmanCode(minHeap.top(),"", out, compressionSize);
		out.close();
		cout<<compressionSize<<endl;
}


int main(){
		vector<int> characters;
		vector<int> frequencies;
		string singleCharacterLine;
		while(getline(cin,singleCharacterLine)){
				std::istringstream iss(singleCharacterLine);
				std::vector<std::string> results(
								(std::istream_iterator<std::string>(iss)),
								std::istream_iterator<std::string>());
				stringstream geek(results[0]);
				int character = 0;
				geek >> character;

				stringstream star(results[1]);
				int freq = 0;
				star >> freq;

				characters.push_back(character);
				frequencies.push_back(freq);
		}
		constructHuffmanCode(characters,frequencies,characters.size());
		return 0;
}

























