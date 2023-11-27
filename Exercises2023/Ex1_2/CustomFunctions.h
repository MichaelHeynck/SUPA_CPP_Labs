#pragma once

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int readLinesFromFile(string, vector<float>&, vector<float>&);

void print(vector<float>, int);

void print(string, vector<float>, vector<float>, int);

void print(string, vector<float>, string[]);

void printData(string);

int magnitude(vector<float>, vector<float>, vector<float>&);

int fit(vector<float>, vector<float>, vector<float>&);

int fit(vector<float>, vector<float>, vector<float>, vector<float>, vector<float>&);

int getLength(vector<float>);

int sum(vector<float>);

int dotProduct(vector<float>, vector<float>);

int save(string, vector<float>, string[]);