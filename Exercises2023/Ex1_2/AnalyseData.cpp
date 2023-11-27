#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <math.h>
#include "CustomFunctions.h"

using namespace std;


int main (){

    vector<float> xvec, yvec, xvec_err, yvec_err;
    int data_lines=0;
    string input_string, file_name_data, file_name_error;

    file_name_data="input2D_float.txt";
    file_name_error="error2D_float.txt";

    data_lines=readLinesFromFile(file_name_data, xvec, yvec);
    readLinesFromFile(file_name_error, xvec_err, yvec_err);

    cout<<"Loaded "<<data_lines<<" lines of data from "<<"\""<<file_name_data<<"\""<<endl;

    bool go=true;

    while(go){

        cout<<"\nWhat function should be used?\n"<<endl;
        cout<<"[1]: Print data"<<endl;
        cout<<"[2]: Linear fit"<<endl;
        cout<<"[3]: Magnitudes"<<endl;
        cout<<"[4]: Powers"<<endl;
        cin>>input_string;

        switch(stoi(input_string)){

            case 1:{
                cout<<"How many lines?"<<endl;
                cin>>input_string;
                data_lines=stoi(input_string);
                print("x,y", xvec, yvec, data_lines);
                break; 
            }
            case 2:{
                vector<float> fit_param;
                fit_param=fit(xvec, yvec, xvec_err, yvec_err);
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
                save("Powers.txt", "x^((int)y)", powers);
                print("Powers, x^((int)y)", powers);
                break;
            }
            default: {
                cout<<"End"<<endl;
                go=false;
                break;

            }

        }

    }
    if(input_string=="1"){

        
    }


    if(input_string=="2"){

        
        //fi=fit(xvec, yvec, param);

    }



}   


