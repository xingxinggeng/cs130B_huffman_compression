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
#include <bitset>
#include <unordered_map>


using namespace std;


void trim(string& s)
{
   size_t p = s.find_first_not_of(" \t");
   s.erase(0, p);

   p = s.find_last_not_of(" \t");
   if (string::npos != p)
      s.erase(p+1);
}


int main(int argc, char* argv[]){

	ifstream infile(argv[1]);

	string line = "";
	
	unordered_map<string, int> table;
	

	while (getline(infile, line)){
		istringstream iss (line);
		int asc;
		iss >> asc;
		string huffcode= line.substr(3);
		trim(huffcode);
		//pq.push(new Node(asc,fre,0,0));
		table[huffcode]=asc;
	}
	

	string res ="";
	char c;
	while( cin.get(c)){
		res=res+bitset<8>(c).to_string();
	}
	


	string tail= res.substr(res.size()-16);
	int validBits= stoi(tail.substr(13),nullptr,2);
	res = res.substr(0, res.size()-16);
	res = res+ tail.substr(0,validBits);


	string current="";
	for(int i=0; i<res.size(); i++){
		current += res[i];
		if(table.find(current)!= table.end()){
			cout<<static_cast<char>(table[current]);
			current="";
		}
	}


	return 0;
}