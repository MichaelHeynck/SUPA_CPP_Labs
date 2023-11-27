
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

float power(float base, float exponent){

    int exp;

    exp=(int)exponent;

    if(exponent-exp>=0.5){
        exp++;
    }

    if(exp==0){
        return 1;
    }
    if(exp==1){
        return base;
    }
    else{
        return base*power(base, exp-1);
    }
}

vector<float> power(vector<float> xvec, vector<float> yvec){

    int N;
    vector<float> powers;
    N=getLength(xvec);

    for(int i=0; i<=N-1; i++){
        powers.push_back(power(xvec[i], yvec[i]));
    }   

    return powers;

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

    //cout<<"Line"<<lines<<":"<<x<<","<<y<<"|Seperator:"<<sep<<endl;
    
    lines++;
    }
    lines-=2; //substract the first line and the atrifical last+1
    data_file.close();
    return lines;
}


void print(vector<float> vec, int lines){

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

void print(string line0, vector<float> vec, string names[]){

    int length; 

    length=getLength(vec);

    cout<<line0<<endl;

    for(int i=0; i<=length-1; i++){
        cout<<names[i]<<": "<<vec[i]<<endl;
    }   
}

void print(string line0, vector<float> vec){

    int length; 

    length=getLength(vec);

    cout<<line0<<endl;

    for(int i=0; i<=length-1; i++){
        cout<<vec[i]<<endl;
    }   
}

void print(string line0, vector<float> vec1, vector<float> vec2, int lines){

    int default_lines=5;
    int plot_lines=lines;
    int length; 

    length=getLength(vec1);

    if(lines>length){
        cout<<"Requested number of lines not available. Here are "<<default_lines<<endl;
        plot_lines=default_lines;
    }

    cout<<line0<<endl;
    for(int i=0; i<=plot_lines-1; i++){
        cout<<vec1[i]<<","<<vec2[i]<<endl;
    }   
}


vector<float> magnitude(vector<float> xvec , vector<float> yvec){

    int length;
    float m;
    vector<float> mag;

    length=getLength(xvec);

    for(int i=0; i<=length-1; i++){
            m=sqrt(power(xvec[i], 2)+power(yvec[i], 2));
            mag.push_back(m);
    }

    return mag;

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

int save(string name, string line0, vector<float> vector_data, string names[]){

    ofstream file;
    int length;

    file.open(name);

    length=getLength(vector_data);

    if(file.fail()){
        cout<<"Problem with opening the file "<<"\""<<name<<"\""<<endl;
        return -1;
    }

    file<<line0<<endl;
    for(int i=0; i<=length-1; i++){
        if(i<length-1){
            file<<names[i]<<": "<<vector_data[i]<<endl;
        }
        else{
            file<<names[i]<<": "<<vector_data[i];
        }
        
    }

    file.close();

    return 1;
}

int save(string name, string line0, vector<float> vector_data){

    ofstream file;
    int length;

    file.open(name);

    length=getLength(vector_data);

    if(file.fail()){
        cout<<"Problem with opening the file "<<"\""<<name<<"\""<<endl;
        return -1;
    }

    file<<line0<<endl;
    for(int i=0; i<=length-1; i++){
        if(i<length-1){
            file<<vector_data[i]<<endl;
        }
        else{
            file<<vector_data[i];
        }
    }

    file.close();

    return 1;
}



vector<float> fit(vector<float> xvec, vector<float> yvec, vector<float> xvec_err, vector<float> yvec_err){

    int N;
    float p, q;
    string names[2];
    vector<float> param;
    N=getLength(xvec);

    float sumx, sumy, prodxx, prodxy, chi2=0;

    sumx=sum(xvec);
    sumy=sum(yvec);

    prodxx=dotProduct(xvec, xvec);
    prodxy=dotProduct(xvec, yvec);


    p=( N*prodxy - sumx*sumy) / ( N*prodxx -sumx*sumx);

    q=( prodxx*sumy - prodxy*sumx) / ( N*prodxx - sumx*sumx );

    for(int i=0; i<=N-1; i++){
        0;
       // chi2+=( ( (yvec[i]-linFunc(xvec[i], p, q))*(yvec[i]-linFunc(xvec[i], p, q))) / () );
    }

    param.push_back(p);
    param.push_back(q);
    names[0]="p";
    names[1]="q";

    print("y=p*x+q", param, names);
    save("FitParameters.txt", "y=p*x+q", param, names);

    return param;
}

float linFunc(float x, float p, float q){

    return p*x+q;
}

