#include <iostream>
#include <map>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

int main(){
		map<char,int> myMap;//(key, count)
		ifstream infile;
		char singleChar;

		char c;
		while (cin.get(c)) {
			if(myMap.find(c) != myMap.end()){//we find a char in myMap
                        myMap[c] += 1;//count +1
                }
                else{
                        myMap[c] = 1;
                }
		}
		/*infile.open("sample.in");
		if(infile.fail()){
				cerr<<"Could not open file"<<endl;
				exit(1);
		}

		while (infile.get(singleChar)){
				if(myMap.find(singleChar) != myMap.end()){//we find a char in myMap
						myMap[singleChar] += 1;//count +1
				}
				else{
						myMap[singleChar] = 1;
				}
		}
		infile.close();*/
		//here we have a map with all characters and their corresponding occurrences
		map<char,int>::iterator it;
		for( it = myMap.begin(); it != myMap.end(); it++){
				printf("%-3d\t%-d\n", int(it->first), it->second);
				//cout<< int(it->first) <<"    "<< it->second <<endl;
		}
		return 0;
}




