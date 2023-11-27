#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <math.h>
#include "CustomFunctions.h"

using namespace std;


int main (){

    vector<float> xvec, yvec, xvec_err, yvec_err, magnitudes, param;

    int data_lines=0, fi;
    string input_string, file_name_data, file_name_error;

    file_name_data="input2D_float.txt";
    file_name_error="error2D_float.txt";

    data_lines=readLinesFromFile(file_name_data, xvec, yvec);

    cout<<"Loaded "<<data_lines<<" lines of data from "<<"\""<<file_name_data<<"\""<<endl;
    cout<<"What function should be used?\n"<<endl;

    cout<<"[1]: Print data"<<endl;

    cout<<"[2]: Linear fit"<<endl;

    cin>>input_string;



    if(input_string=="1"){

        cout<<"How many lines?"<<endl;
        cin>>input_string;
        data_lines=stoi(input_string);
        print("x,y", xvec, yvec, data_lines);
    }


    if(input_string=="2"){

        data_lines=readLinesFromFile(file_name_error, xvec_err, yvec_err);
        //fi=fit(xvec, yvec, xvec_err,  yvec_err, param);
        fi=fit(xvec, yvec, param);

    }



}   

void nothing(){

    vector<float> xvec, yvec, magnitudes, param;

    int data_lines=0;

    data_lines=readLinesFromFile("input2D_float.txt", xvec, yvec);
    cout<<data_lines<<endl;


    cout<<"The x-Array contains:"<<endl;
    print(xvec, data_lines);


    cout<<"The y-Array contains:"<<endl;
    print(yvec, data_lines);

    int magl=0;
    magl=magnitude(xvec, yvec, magnitudes);


    cout<<"The magnitudes are:"<<endl;
    print(magnitudes, magl);

    int fi;

    fi=fit(xvec, yvec, param);
    cout<<"The p and q parameters are:"<<endl;
    print(param, 2);

}

