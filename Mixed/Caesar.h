#pragma once
#ifndef CAESAR_H
#define CAESAR_H

#include <string>
using namespace std;

class Caesar {
private:
    string str;
    int size;

public:
    Caesar(const string& input, int n);

    void print(const string& str, int size);

    string encryption(const string& text, const string& esh, const string& desh, int size);
    string decryption(const string& text, const string& esh, const string& desh, int size);
};

#endif 
