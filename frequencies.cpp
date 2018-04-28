#include <iostream>
#include <map>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

int main(){
		map<char,int> myMap;//(key, count)
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
		map<char,int>::iterator it;
		for( it = myMap.begin(); it != myMap.end(); it++){
				printf("%-5d\t%-d\n", int(it->first), it->second);
		}
		return 0;
}




