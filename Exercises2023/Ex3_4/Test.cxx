/*
Author: Michael Heynck


*/



#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <math.h>
#include "FiniteFunctions.h"

using namespace std;
    

int main (){

ifstream data_file;

data_file.open("/workspaces/SUPA_CPP_Labs_mh2065/Exercises2023/Ex3_4/Outputs/data/MysteryData24212.txt");
if(data_file.fail()){
    cout<<"Problem with opening the file"<<endl;
    return -1;
}
double x;  
int lines=1;
vector<double> xvec;

while(!data_file.eof()){
data_file>>x;
xvec.push_back(x);
lines++;
}
lines-=1; 
data_file.close();




CauchyLorentzFunction ff(-10,10,0,-2,"gamma");
ff.plotData(xvec, 100, true);
ff.plotFunction();
ff.~CauchyLorentzFunction();

}