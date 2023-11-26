#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <math.h>
#include "CustomFunctions.h"
using namespace std;


int main (){
 

    vector<float> xvec, yvec, magnitudes, param;

    int data_lines=0;

    data_lines=readLinesFromFile("input2D_float.txt", xvec, yvec);
    cout<<data_lines<<endl;


    cout<<"The x-Array contains:"<<endl;
    printArray(xvec, data_lines);


    cout<<"The y-Array contains:"<<endl;
    printArray(yvec, data_lines);

    int magl=0;
    magl=magnitude(xvec, yvec, magnitudes);


    cout<<"The magnitudes are:"<<endl;
    printArray(magnitudes, magl);

    int fi;

    fi=fit(xvec, yvec, param);
    cout<<"The p and q parameters are:"<<endl;
    printArray(param, 2);

}   

