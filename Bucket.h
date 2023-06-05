/*
 *  Bucket.h
 *  Isaac Monheit & Kabir Pamnani
 *  04/23/2022
 *
 *  CS 15 Proj3
 *
 *  The interface of Bucket.cpp, meaning that it contains 
 *  the function declarations and headers of the Bucket class
 *
 */


#ifndef BUCKET_H
#define BUCKET_H

#include "fileStruct.h"
#include <vector>

class Bucket {

public:
    fileStruct at(int index);
    std::string keyAt(int index);
    int lineNumAt(int index);
    std::string fileNameAt(int index);
    bool isEmpty();
    int size();
    void insert(const fileStruct &keyValue);

    void printBucket();
private:
    std::vector<fileStruct> vect;
};



#endif