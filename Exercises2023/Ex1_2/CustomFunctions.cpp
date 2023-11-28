
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;


//get the number of elements in a vector
int getLength(vector<float> vec){
    int length=0;
    for (auto i : vec){
        length++;
    }
    return length;
}

//calculate the power of a base number with an exponent. The exponent is rounded to the nearest integer
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

//calculate the power for each element of two vectors, xvec being the base and yvec being the exponents
vector<float> power(vector<float> xvec, vector<float> yvec){

    int N;
    vector<float> powers;
    N=getLength(xvec);

    for(int i=0; i<=N-1; i++){
        powers.push_back(power(xvec[i], yvec[i]));
    }   

    return powers;

}

//read two colums seperated by a "," and save them in the vectors provided in the argument
int readLinesFromFile(string file_name, vector<float>& xvec, vector<float>& yvec){

    ifstream data_file;

    data_file.open(file_name);
    if(data_file.fail()){
        cout<<"Problem with opening the file"<<endl;
        return -1;
    }

    float x, y; 
    char sep, x_name, y_name; 
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

    
    lines++;
    }
    lines-=2; //substract the first line and the atrifical last+1
    data_file.close();
    return lines;
}

//print a vector. The first line to be printed is a string containing information about the printed values of the vector. Each line contains a specific name and a following element form the vector 
void print(string line0, vector<float> vec, string names[]){

    int length; 

    length=getLength(vec);

    cout<<line0<<endl;

    for(int i=0; i<=length-1; i++){
        cout<<names[i]<<": "<<vec[i]<<endl;
    }   
}

//just print one element per line, the elements are provided by a vector. The first line is a string containing infomartion about the printed vector
void print(string line0, vector<float> vec){

    int length; 

    length=getLength(vec);

    cout<<line0<<endl;

    for(int i=0; i<=length-1; i++){
        cout<<vec[i]<<endl;
    }   
}

//print two vectors, two elements per line and seperated by a ",". The first line provides information about the printed vectors. If the number of requested lines is larger than the size of the vectores, print only 5 lines
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

//calculate and return  a vector containing the magnitude (sqrt(x^2+y^2)) of the given XY-vector, defined as two vectors (x and y coordinate with origin at (0,0))
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

//calculate the sum over each element of a vector 
float sum(vector<float> vec){

    float sum=0;
    for (auto i : vec){
        sum+=i;
    }

    return sum;
}

//calculate the dot product of a vector (sum over the product of two elements at the same position of a vector)
float dotProduct(vector<float> vec1, vector<float> vec2){

    int length;
    float sum=0;
    length=getLength(vec1);

    for(int i=0; i<=length-1; i++){
        sum+=(vec1[i]*vec2[i]);
    }
    return sum;
}   

//save the data of a vector. Each lines contains a name and a data element. The first line contains information about the saved data. The File can be named with a string.
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

//Save the data of a vector. The first line provides information about the saved data. The filename is determined by a string 
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

//calculates the output of a linear function y=p*x=q
float linFunc(float x, float p, float q){

    return p*x+q;
}

//calculates the the paramaters p and q of a linear fit using the least sqares method. Also calculates the chi sqaured divided by the numbers of freedom to estimate the goodness of the fit
//The result is saved as a vector, the first element is the p value, the second element is the q value and the thrid element is the chi squared value devided by the number of freedom
vector<float> fit(vector<float> xvec, vector<float> yvec, vector<float> xvec_err, vector<float> yvec_err){

    int N;
    float p, q;
    string names[3];
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
        chi2+=( power((yvec[i]-linFunc(xvec[i], p, q)), 2) / power(yvec_err[i], 2) );
    }



    chi2/=(N-2);
    param.push_back(p);
    param.push_back(q);
    param.push_back(chi2);
    names[0]="p";
    names[1]="q";
    names[2]="chi^2";

    print("y=p*x+q", param, names);
    save("FitParameters.txt", "y=p*x+q", param, names);

    return param;
}


