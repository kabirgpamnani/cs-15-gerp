/*
 *  structList.h
 *  Isaac Monheit and Kabir Pamnani
 *  Spring 2022
 *
 *  CS 15 proj3
 *
 *  
 *
 */

#ifndef STRUCT_LIST_H
#define STRUCT_LIST_H

#include "fileStruct.h"
#include <vector>

using namespace std;

class DatumStack {

public:
    structList();
    ~structList();

    void clear();
    int size();
    wordInfo elementAt();
private:
    vector<wordInfo> fileList;
};



#endif