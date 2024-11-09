#pragma once
#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Encryption {
private:
    int rows;
    int columns;

public:
    Encryption(int Rows, int Columns);

    void print(const vector<vector<char>>& Str);
    vector<vector<char>> encr(const vector<vector<char>>& Str);
    vector<vector<char>> decr(const vector<vector<char>>& Str);
};

#endif 

