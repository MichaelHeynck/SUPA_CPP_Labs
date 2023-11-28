#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <math.h>
#include "CustomFunctions.h"

using namespace std;


int main (){

    vector<float> xvec, yvec, xvec_error, yvec_error;
    int data_lines=0;
    string input_string, file_name_data, file_name_error;

    file_name_data="input2D_float.txt";
    file_name_error="error2D_float.txt";

    data_lines=readLinesFromFile(file_name_data, xvec, yvec);
    readLinesFromFile(file_name_error, xvec_error, yvec_error);

    cout<<"This program reads two 2D-files. On of them contains x and y values and the another one the associated error."<<endl; 
    cout<<"Both have to be floats, one pair of x and y values sepetared by a \",\" per line. The first line is a string containing information about the data"<<endl;

    cout<<endl;

    cout<<"There are four functions available:"<<endl;
    cout<<endl;
    cout<<"1: Print data"<<endl;
    cout<<"Print the asked amount of lines from the read file that contains the x and y values."<<endl;

    cout<<endl;
    cout<<"2: Linear fit"<<endl;
    cout<<"Calculates a linear fit to the data using the least squares method. Also calculates the chi2 squared divided by the number of freedom."<<endl;

    cout<<endl;
    cout<<"3: Magnitudes"<<endl;
    cout<<"Calculates the magnitudes (sqrt(x^2+y^2)) of the vectors (origin at (0,0)) of the data."<<endl;

    cout<<endl;
    cout<<"4: Powers"<<endl;
    cout<<"Calculates the powers (x^y) of the data points. The y values are rounded to the nearest integer."<<endl;

    cout<<endl;
    cout<<"Loaded "<<data_lines<<" lines of data from "<<"\""<<file_name_data<<"\""<<endl;

    bool go=true;

    while(go){

        cout<<"\nWhat function should be used?\n"<<endl;
        cout<<"[1]: Print data"<<endl;
        cout<<"[2]: Linear fit"<<endl;
        cout<<"[3]: Magnitudes"<<endl;
        cout<<"[4]: Powers"<<endl;
        cout<<"[0]: Exit"<<endl;
        cin>>input_string;

        switch(stoi(input_string)){
            case 0:{
                cout<<"Exit program"<<endl;
                go=false;
                break;
            }
            case 1:{
                cout<<"How many lines?"<<endl;
                cin>>input_string;
                data_lines=stoi(input_string);
                print("x,y", xvec, yvec, data_lines);
                break; 
            }
            case 2:{
                vector<float> fit_param;
                fit_param=fit(xvec, yvec, xvec_error, yvec_error);
                break;
            }

            case 3:{
                vector<float> magnitudes;
                magnitudes=magnitude(xvec, yvec);
                save("Magnitudes.txt", "sqrt(x_i*x_i+y_i*y_i)", magnitudes);
                print("Magnitudes, sqrt(x_i*x_i+y_i*y_i)", magnitudes);
                break;
            }

            case 4:{
                vector<float> powers;
                powers=power(xvec, yvec);
                save("Powers.txt", "x_i^((int)y_i)", powers);
                print("Powers, x_i^((int)y_i)", powers);
                break;
            }
            default: {
                cout<<"Invalid input"<<endl;
                go=false;
                break;
            }
        }
    }
}   


