#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <math.h>
using namespace std;


int readLinesFromFile(string, vector<float>&, vector<float>&);

int readLinesFromFile(string file_name, vector<float>& xvec, vector<float>& yvec){

    ifstream data_file;

    data_file.open(file_name);
    if(data_file.fail()){
        cout<<"Problem with opening the file"<<endl;
        return -1;
    }

    float x, y; //variables that hold the x and y value per line 
    char sep, x_name, y_name; // character that seperates the x and y values
    int lines=1;
    
    while(!data_file.eof()){
     if(lines==1){
        lines++;
        data_file>>x_name>>sep>>y_name;
        continue;
     }
    data_file>>x>>sep>>y;
    xvec.push_back(x);
    yvec.push_back(y);

    cout<<"Line"<<lines<<":"<<x<<","<<y<<"|Seperator:"<<sep<<endl;
    
    lines++;
    }
    lines-=2; //substract the first line and the atrifical last+1
    data_file.close();
    return lines;
}

void printArray(vector<float>, int);

void printArray(vector<float> vec, int lines){

    int default_lines=5;
    int plot_lines=lines;
    int length=0; //legth (number of elements) of the vector

    for (auto i : vec){
        length++;
    }

    if(lines>length){
        cout<<"Requested number of lines not available. Here are "<<default_lines<<endl;
        plot_lines=default_lines;
    }

    for(int i=0; i<=plot_lines-1; i++){
        cout<<vec[i]<<endl;
    }   
}


int magnitude(vector<float>&, vector<float>&, vector<float>&);

int magnitude(vector<float>& xvec , vector<float>& yvec, vector<float>& mag){

int length=0;
float m;
for (auto i : xvec){
        length++;
    }


for(int i=0; i<=length-1; i++){
        m=sqrt(xvec[i]*xvec[i]+yvec[i]*yvec[i]);
        mag.push_back(m);
    }


return length;

}



int main (){
 

    vector<float> xvec, yvec, magnitudes;

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

    
}   

