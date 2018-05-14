#include <stdio.h>
#include <algorithm>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>  
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;


int main(){
    //ifstream in("sample.in");
    int count[256]={0};

    char c;
    while(cin.get(c)){
        if(c==EOF){
	    break;
        }
	    count[(int)c]++;
    }

    for(int i=0; i<256; i++){
	    if(count[i]!=0){
		    cout << i << "	"<< count[i] <<endl;
	    }
    }
    //in.close();
    return 0;


}
