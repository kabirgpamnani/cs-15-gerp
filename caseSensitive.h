/*
 *  PassengerQueue.h
 *  Isaac Monheit
 *  2/12/2022
 *
 *  CS 15 Proj1 
 *
 *  Header file that introduces all the public and private functions for
 *  PassengerQueue.cpp
 *
 */


#ifndef CASE_SENSITIVE_H
#define CASE_SENSITIVE_H

#include "fileStruct.h"
#include <vector>

class caseSensitive {

public:
    fileStruct elementAt(int index);
    std::string keyAt(int index);
    int size();
    void insert(const fileStruct &keyValue);

private:
    std::vector<fileStruct> vect;
};



#endif