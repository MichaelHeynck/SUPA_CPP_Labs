#pragma once

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int readLinesFromFile(string, vector<float>&, vector<float>&);


void print(string, vector<float>, vector<float>, int);

void print(string, vector<float>, string[]);

void print(string, vector<float>);

vector<float> magnitude(vector<float>, vector<float>);

vector<float> fit(vector<float>, vector<float>, vector<float>, vector<float>);

int getLength(vector<float>);

float sum(vector<float>);

float dotProduct(vector<float>, vector<float>);

int save(string, string, vector<float>, string[]);

int save(string, string, vector<float>);

float power(float, float);

vector<float> power(vector<float>, vector<float>);

float linFunc(float, float, float);