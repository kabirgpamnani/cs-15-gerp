/*
 *  structArray.h
 *  Isaac Monheit and Kabir Pamnani
 *  Spring 2022
 *
 *  CS 15 proj3
 *
 *  
 *
 */

#ifndef STRUCT_ARRAY_H
#define STRUCT_ARRAY_H

#include "Datum.h"
#include <vector>

using namespace std;

class DatumStack {

public:
    DatumStack();
    DatumStack(Datum arr[], int size);

    bool isEmpty();
    void clear();
    int size();
    Datum top();
    void pop();
    void push(const Datum &datum);
private:
    vector<Datum> stack;
};



#endif