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






NormalDistributionFunction ND(-10, 10, 2, 3, "NormalDistribution");
ND.printInfo();
ND.plotData(xvec, 500, true);
ND.plotFunction();
//ND.~NormalDistributionFunction(); //causes weird error

CauchyLorentzFunction CLD(-10, 10, 2, 3, "CauchyLorentzDistribution");
CLD.printInfo();
CLD.plotData(xvec, 500, true);
CLD.plotFunction();
//CLD.~CauchyLorentzFunction(); //causes weird error

vector<double> samples;

NegativeCrystalBallDistribution NCBD(-25, 25, 2, 5, 0.5, 2, "NegativeCrystalBallDistribution");
NCBD.printInfo();
NCBD.plotData(xvec, 500, true);
samples=NCBD.metropolis(10000, 2);
NCBD.plotData(samples, 500, false);
NCBD.plotFunction();
//NCBD.~NegativeCrystalBallDistribution(); //causes weird error

}