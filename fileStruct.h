/*
 *  fileStruct.h
 *  Isaac Monheit & Kabir Pamnani
 *  Spring 2022
 *
 *  CS 15 proj3 
 *
 *  Holds the declaration of the struct called fileStruct,
 *  which contains member variables that store information about the 
 *  files being indexed.
 *
 */

#ifndef FILESTRUCT_H
#define FILESTRUCT_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct fileStruct {
    string key, fileName;
    int lineNum;

    // default constructor
    fileStruct() {
        key = "-1";
        lineNum = -1;
        fileName = "";
    }

    // constructor that initializes member values with arguments passed in
    fileStruct(string newKey, string newFileName, int newLineNum) {
        key = newKey;
        lineNum = newLineNum;
        fileName = newFileName;
    }
};

#endif

