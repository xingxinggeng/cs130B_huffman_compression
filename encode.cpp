//Q: int main(int argc, char *argv[]) , argv[1] is a pointer, why can be used directly as a string
//line 57: 832 &833
//explicitlt include valid bits at the front of the compression file?
//will it automatically pad last extra bits with zeros see line 63

#include <iostream>
#include <fstream>
#include <iterator>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <bitset>
using namespace std;

int main(int argc, char *argv[]){
		map<char,string> codeWords;
		map<char,int> frequency;
		int valid_bits = 0;
		string compression;
//get codeWords map
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

				codeWords[ char(character) ] = huff_code;
        }
		infile.close();

//get frequency map
        char c;
        while (cin.get(c)) {
			compression += codeWords[c];
            if(frequency.find(c) != frequency.end()){//we find a char in myMap
                        frequency[c] += 1;//count +1
                }
            else{
                        frequency[c] = 1;
            }
        }

//explicit vaild bits
		map<char,int>::iterator it;
        for( it = frequency.begin(); it != frequency.end(); it++){
		//		cout<<int(it->first)<<"    "<<codeWords[it->first]<<"     "<<it->second<<endl;
				valid_bits += (codeWords[it->first]).length() * it->second;// valid bits
		}
//		cout<<"test for valid_bits  "<<valid_bits<<endl;
		string binary_validBits = bitset<32>(valid_bits).to_string();//crucial 
//		cout<<"test for binaryvalid_bits  "<<binary_validBits<<endl;
		string binaryString = binary_validBits + compression;
//		cout<<"testfor binarystring\n"<<binaryString<<endl;
		string byteString = "";
		string output_string = "";
		double stringLength  = binaryString.length();
		int i ;
		for( i = 0; stringLength > (binaryString.length() % 8) ; i++){
				if( !(((i+1)%8) == 0 )){
						byteString += binaryString[i];
						stringLength --;
				}
				else{
						byteString += binaryString[i];
						int i = std::stoi(byteString, nullptr, 2);
						output_string = output_string + char(i) ;
						stringLength --;
						byteString = "";
				}
		}
		string bytePadding  = "";
		for(int j = binaryString.length() - stringLength; j < binaryString.length(); j++){
				bytePadding += binaryString[j];
		}
		for(int p = stringLength ; p < 8; p++){
				bytePadding += "0";
		}

		int k = std::stoi(bytePadding, nullptr, 2);
		output_string += char(k);
		cout<<output_string;
		return 0;
}



