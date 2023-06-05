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


#ifndef BUCKET_LIST_H
#define BUCKET_LIST_H

#include "caseSensitive.h"
#include <vector>

class bucketList {

public:
    caseSensitive caseAt(int index);
    int size();
    void insert(const caseSensitive &oneCase);

private:
    std::vector<caseSensitive> bucket;
};



#endif