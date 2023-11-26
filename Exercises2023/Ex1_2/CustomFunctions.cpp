
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;



int getLength(vector<float> vec){
    int length=0;
    for (auto i : vec){
        length++;
    }
    return length;
}

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


void printArray(vector<float> vec, int lines){

    int default_lines=5;
    int plot_lines=lines;
    int length; 

    length=getLength(vec);

    if(lines>length){
        cout<<"Requested number of lines not available. Here are "<<default_lines<<endl;
        plot_lines=default_lines;
    }

    for(int i=0; i<=plot_lines-1; i++){
        cout<<vec[i]<<endl;
    }   
}


int magnitude(vector<float>& xvec , vector<float>& yvec, vector<float>& mag){

    int length;
    float m;

    length=getLength(xvec);

    for(int i=0; i<=length-1; i++){
            m=sqrt(xvec[i]*xvec[i]+yvec[i]*yvec[i]);
            mag.push_back(m);
    }

    return length;

}

float sum(vector<float> vec){

    float sum=0;
    for (auto i : vec){
        sum+=i;
    }

    return sum;
}

float dotProduct(vector<float> vec1, vector<float> vec2){

    int length;
    float sum=0;
    length=getLength(vec1);

    for(int i=0; i<=length-1; i++){
        sum+=(vec1[i]*vec2[i]);
    }
    return sum;
}   

int fit(vector<float>& xvec, vector<float>& yvec, vector<float>& param){

    int N;
    float p, q;
    N=getLength(xvec);

    float sumx, sumy, prodxx, prodxy;

    sumx=sum(xvec);
    sumy=sum(yvec);

    prodxx=dotProduct(xvec, xvec);
    prodxy=dotProduct(xvec, yvec);


    p=( N*prodxy - sumx*sumy) / ( N*prodxx -sumx*sumx);

    q=( prodxx*sumy - prodxy*sumx) / ( N*prodxx - sumx*sumx );

    param.push_back(p);
    param.push_back(q);

    string s;

    return 1;
}

