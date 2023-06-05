/*
 *  ht.h
 *  Isaac Monheit and Kabir Pamnani
 *  Spring 2022
 *
 *  CS 15 proj3 
 *
 *  The interface of ht.cpp. Contains function declarations, headers 
 *  and private/public member variables needed for the implementation
 *  of the hash table.
 *
 */

#ifndef HT_H
#define HT_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <vector>
#include "FSTree.h"
#include "DirNode.h"
#include "fileStruct.h"
#include "Bucket.h"

using namespace std;

class ht {

public:
    ht();
    ~ht();

    void treeTraversal(DirNode *node, vector<DirNode*> 
    &filePath, string &fileName);

    void command_loop(istream &input, ofstream &output);

    template<typename streamtype>
    void open_or_die(streamtype &stream, string filename);

private: 
    vector<Bucket> hashTable;
    int capacity;
    int hashSize;

    void expandHash();

    bool checkBucket(int hashNum, string &key);
    string lowerCase(string word);
    bool duplicateCheck(fileStruct &newStruct, int hashNum);
    void rehash();
    
    int compressed_hash(string &word);
    void file_parse(string &filename);
    void basic_insert(string &word);

    void hashTableSampleCreation();

    void hashBucketPrint(int index);

    void insert(string &key, string &filename, int &lineNum);


    void search(string word, ostream &output);
    int caseBucketCheck(int hashNum, string key);
    void printCaseSens(int bucket, string key, ostream &output);

    void insensitiveSearch(string word, ostream &output);
    int insensitiveBucketCheck(int hashNum, string key);
    void printCaseInsens(int bucket, ostream &output);
    
    

};



#endif