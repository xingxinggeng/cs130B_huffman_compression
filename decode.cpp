#include <iostream>
#include <iterator>
#include <string>
#include <map>
#include <bitset>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]){
		map<string, char> codeWords;//["0102","a"]
		string compression;

//get codewords map
		ifstream infile;
		infile.open(argv[1]);
		string singleLine;

		while(getline(infile,singleLine)){
				std::istringstream iss(singleLine);
                std::vector<std::string> results(
                               (std::istream_iterator<std::string>(iss)),
                                std::istream_iterator<std::string>());
                stringstream geek(results[0]);
                int character = 0;
                geek >> character;

                stringstream star(results[1]);
                string huff_code = ""; 
                star >> huff_code;

                codeWords[huff_code ] = char(character);
        }   
        infile.close();
		
		string binaryString = "";
		char c;
		while(cin.get(c)){
				binaryString += bitset<8>(int(c)).to_string();
		}
		string valid_bits = binaryString.substr(0,32);
//		cout<< valid_bits<<endl;
		int validBits = std::stoi(valid_bits, nullptr, 2);
//		cout<<validBits<<endl;
		
		string realString  = binaryString.substr(32,validBits);
		string output_string = "";
		string token = "";
//		cout<<codeWords[realString.substr(0,5)]<<"\n"<<codeWords[realString.substr(5,4)]<<"\n"<<codeWords[realString.substr(9,4)]<<"\n";
		for(int i = 0; i < validBits; i++){
				if(codeWords.find(token) != codeWords.end()){
						output_string += codeWords[token];
					//	cout<<codeWords[token]<<endl;
						token = realString[i];
				}
				else{
						token += realString[i];
				}
		}
		cout<<output_string;
		return 0;
}




