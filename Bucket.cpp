/*
 *  Bucket.cpp
 *  Isaac Monheit & Kabir Pamnani
 *  4/20/2022
 *
 *  CS 15 Proj3
 *
 *  Implementation and definition of all the header functions in
 *  Bucket.h. This file contains a list of functions that are used for 
 *  accessing different members of the struct "fileStruct." 
 *
 */


#include <iostream>
#include "fileStruct.h"
#include "Bucket.h"
#include <vector>


/*
 * name:      at
 * purpose:   find element at given index
 * arguments: int var of the index
 * returns:   fileStruct at given index in vector
 */
fileStruct Bucket::at(int index)
{
    return vect.at(index);
}

/*
 * name:      keyAt
 * purpose:   find key (word) at given index
 * arguments: int var of the index
 * returns:   string of the word at given index in vector
 */
std::string Bucket::keyAt(int index)
{
    return vect.at(index).key;
}

/*
 * name:      lineNumAt
 * purpose:   find line number at given index
 * arguments: int var of the index
 * returns:   int var of line number
 */
int Bucket::lineNumAt(int index)
{
    return vect.at(index).lineNum;
}

/*
 * name:      fileNameAt
 * purpose:   find full file path at given index
 * arguments: int var of the index
 * returns:   string of the file path at given index
 */
std::string Bucket::fileNameAt(int index)
{
    return vect.at(index).fileName;
}

/*
 * name:      insert
 * purpose:   inserts a fileStruct to the back of vector
 * arguments: struct called "fileStruct"
 * returns:   none
 */
void Bucket::insert(const fileStruct &keyValue)
{
    vect.push_back(keyValue);
}

/*
 * name:      size()
 * purpose:   returns size of vector
 * arguments: none
 * returns:   int size of vector
 */
int Bucket::size()
{
    return vect.size();
}

/*
 * name:      isEmpty()
 * purpose:   checks if vector is empty 
 * arguments: none
 * returns:   bool result of if vector is empty
 */
bool Bucket::isEmpty()
{
    return vect.empty();
}

/*
 * name:      printBucket()
 * purpose:   used for testing purposes to output the values 
 *            in the struct associated with the specified key
 * arguments: none
 * returns:   none
 */
void Bucket::printBucket()
{
    for (int i = 0; i < size(); i++) {
        cout << "Slot #" << i << ":\n";
        cout << "        Key: " << keyAt(i) << endl;
        cout << "Line Number: " << lineNumAt(i) << endl;
        cout << "  File Name: " << fileNameAt(i) << endl;
    }
}



