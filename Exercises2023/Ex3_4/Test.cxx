/*
Author: Michael Heynck

Date: 11/12/2023
*/



#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <random>
#include "FiniteFunctions.h"

using namespace std;
    

/*
Assume a circle with radius r inside square of length 2r.

number density rho (numbers N per area A) is uniform, rho_circle==rho_square ==> N_square/A_square==N_circle/A_circle ==>
==> N_square/((2*r)^2)==N_circle/(pi*r^2) ==> pi=4*N_circle/N_square

*/
float getPi(float radius, int n_random){
    
    
    float random_x, random_y;
    int counter_circle=0, counter_square=0;

    random_device rd;
    mt19937 mtEngine{1};
    uniform_real_distribution<float> uniformPDF{-radius, radius};

    if(n_random%2!=0){
        n_random++;
    }

    for(int i=0; i<n_random/2; i++){
        random_x=uniformPDF(mtEngine);
        random_y=uniformPDF(mtEngine);

        if(sqrt(random_x*random_x+random_y*random_y)<=radius){
            counter_circle++;
        }
        counter_square++;
    }
    
    return 4*(float)counter_circle/(float)counter_square;   
}



int main (){

// read the data and save it to a vector
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


vector<double> samples; //contains samples collected via the metropolis algorithm

NormalDistributionFunction ND(-25, 25, 2, 3, "NormalDistribution");
ND.printInfo();
ND.plotData(xvec, 500, true);
samples=ND.metropolis(10000, 2);
ND.plotData(samples, 500, false);
ND.plotFunction();


CauchyLorentzFunction CLD(-25, 25, 2, 3, "CauchyLorentzDistribution");
CLD.printInfo();
CLD.plotData(xvec, 500, true);
samples=CLD.metropolis(10000, 2);
CLD.plotData(samples, 500, false);
CLD.plotFunction();




NegativeCrystalBallDistribution NCBD(-25, 25, 2, 5, 0.5, 2, "NegativeCrystalBallDistribution");
NCBD.printInfo();
NCBD.plotData(xvec, 500, true);
samples=NCBD.metropolis(10000, 2);
NCBD.plotData(samples, 500, false);
NCBD.plotFunction();


float pi_radius=1;
int pi_numbers=10000000;
float pi=getPi(pi_radius, pi_numbers);

printf("\nPi is (%1.2E random numbers within square of length %1.2f): %.10f\n", (float)pi_numbers, (float)pi_radius, pi);
printf("Deviation form more precise M_PI is: %.10f - %.10f = %1.1E\n", M_PI, pi, M_PI-pi);


}

