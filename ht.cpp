/*
 *  ht.cpp
 *  Isaac Monheit and Kabir Pamnani
 *  Spring 2022
 *
 *  CS 15 proj3 
 *
 *  Implementation of the Hash Table and functions associated 
 *  with the insertion into and search of the Hash Table
 *
 */


#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <vector>
#include <functional>
#include "FSTree.h"
#include "DirNode.h"
#include "ht.h"
#include "stringProcessing.h"
#include "Bucket.h"
#include "fileStruct.h"

using namespace std;

/*
 * name:      hash table default constructor
 * purpose:   initialize an empty hash table of given capacity
 * arguments: none
 * returns:   none
 * effects:   creates a ht instance
 */
ht::ht() {
    hashSize = 0;
    capacity = 1000000;
    // stopHash = false;
    hashTable.resize(capacity);
}

/*
 * name:      hash table default destructor
 * purpose:   clear the hash table 
 * arguments: none
 * returns:   none
 */
ht::~ht() {
    hashTable.clear();
}

// used for testing successful creation and use of hash table
void ht::hashTableSampleCreation()
{
    //create a fileStruct
    fileStruct newFile1("applE", "kabs/isaac.cpp", 5);
    fileStruct newFile2("Banana", "kabs/kabs.cpp", 6);
    
    // create instances of bucket class 
    Bucket apple;
    Bucket banana;

    // push buckets into hash table
    hashTable.push_back(apple);
    hashTable.push_back(banana);

    // test insertsion of fileStructs into buckets in ht
    hashTable.at(0).insert(newFile1);
    hashTable.at(1).insert(newFile2);

    // isEmpty test
    if (!hashTable.at(0).isEmpty())
        cout << "it is not empty\n";

    cout << "key at line 5 of isaac.cpp = "
         << hashTable.at(0).keyAt(0) << endl;

    fileStruct newFile3;
    hashTable.at(0).insert(newFile3);

    cout << hashTable.at(0).keyAt(1) << endl;

    cout << "key at line 6 of kabs.cpp = "
         << hashTable.at(1).keyAt(0) << endl;

}

/*
 * name:      open_or_die
 * purpose:   handles the opening of a file
 * arguments: streamtype reference to var stream, filename of type string
 * returns:   none
 * effects:   opens file successfully, or outputs error message that
 *            file could not be opened
 */
template<typename streamtype>
void ht::open_or_die(streamtype &stream, string filename)
{
    stream.open(filename);
    if (not stream.is_open()) {
        cerr << "Error: could not open file " + filename << endl;
        exit(EXIT_FAILURE);
    }
}

/*
 * name:      compressed_hash
 * purpose:   turns a word into the compressed hash value
 * arguments: string reference to var word
 * returns:   int compressed hash value
 */
int ht::compressed_hash(string &word) 
{
    int index = hash<string>{}(word) % capacity;
    // cout << "Compressed hash for " << word << " is " << index << endl;

    // cout << word << " ";
    return index;
}


/*
 * name:      lowerCase
 * purpose:   converts a string to all lowercase
 * arguments: string var "word"
 * returns:   lowercase string result of original word
 */
string ht::lowerCase(string word)
{
    string temp;

    // loop through each char of the word
    for (unsigned long int i = 0; i < word.size(); i++)
        // convert each char to lower case using tolower function
        if (isalpha(word.at(i))) {
            temp.push_back(tolower(word.at(i)));
        } else {
            temp.push_back(word.at(i));
        }

    // return lowercase string
    return temp;
}

/*
 * name:      checkBucket
 * purpose:   check if the bucket trying to be inserted into is free or 
 *            has the right key
 * arguments: int hash number value, string reference to key (word)
 * returns:   true if can be inserted into that bucket, false if cannot
 */
bool ht::checkBucket(int hashNum, string &key)
{
    // if specific bucket is empty or the bucket has the right key,
    // return true
    if ((hashTable.at(hashNum).isEmpty()) or 
        (lowerCase(hashTable.at(hashNum).at(0).key) == (lowerCase(key)))) {
        return true;
    } else {
        return false;
    }
}

bool ht::duplicateCheck(fileStruct &newStruct, int hashNum)
{
    int bucketSize = hashTable.at(hashNum).size();
    for (int i = 0; i < bucketSize; i++) {
        if (hashTable.at(hashNum).at(i).fileName == newStruct.fileName) {
            if (hashTable.at(hashNum).at(i).lineNum == newStruct.lineNum) {
                if (hashTable.at(hashNum).at(i).key == newStruct.key) {
                    return true;
                }
            }
        }
    }
    return false;
}

/*
 * name:      hashBucketPrint
 * purpose:   prints bucket at given index
 * arguments: integer var index
 * returns:   none
 */
void ht::hashBucketPrint(int index)
{
    hashTable.at(index).printBucket();
}

/*
 * name:      insert
 * purpose:   inserts every word in every given file into hash table 
 *            (hashes each word to appropriate position) 
 * arguments: string reference to key (word), string reference to filename,
 *            int value of line number
 * returns:   none
 * notes:     expands hash table when it reaches load factor
 */
void ht::insert(string &key, string &filename, int &lineNum)
{
    string lowercaseKey = lowerCase(key);
    int hashNum = compressed_hash(lowercaseKey);

    fileStruct newStruct(key, filename, lineNum);

    //check bucket to see if it's empty or contains the key in question
    if (checkBucket(hashNum, key)) {

        //make sure theres no duplicate structs in the bucket
        // if (!duplicateCheck(newStruct, hashNum)) {

            // cout << "key is " << newStruct.key << endl;
            if (hashTable.at(hashNum).isEmpty())
                hashSize++;
            hashTable.at(hashNum).insert(newStruct);
            // cout << "successful insertion of " << newStruct.key << endl;
        // }
    } else {
        for (int i = hashNum; i < capacity; i++) {
            if (checkBucket(i, key)) {
                // if (!duplicateCheck(newStruct, i)) {
                    // cout << "key is " << newStruct.key << endl;
                    if (hashTable.at(i).isEmpty())
                        hashSize++;
                    hashTable.at(i).insert(newStruct);
                    // cout << "successful insertion of " << newStruct.key << endl;
                // }
                return;
            }
        }
        // cout << "expand happening" << endl;
        expandHash();
        insert(key, filename, lineNum);
    }
    if ((hashSize / capacity) > 0.7)
        expandHash();
}

/*
 * name:      expandHash
 * purpose:   expands hash table when it reaches load factor
 * arguments: none
 * returns:   none
 */
void ht::expandHash() {
   
    cout << "expanding" << endl;

    vector<Bucket> tempHash;

    tempHash.resize(capacity * 2);

    for (int i = 0; i < capacity; i++) {
        if ( not (hashTable.at(i).isEmpty())) {

            string lowercaseKey = lowerCase(hashTable.at(i).at(0).key);
            int hashNum = compressed_hash(lowercaseKey);

            while( not (tempHash.at(hashNum).isEmpty())) {
                hashNum++;
            }
            tempHash.at(hashNum) = hashTable.at(i);
        }
    }

    capacity = capacity * 2;    
    hashTable = tempHash;
}

/*
 * name:      file_parse
 * purpose:   processes each individual word in each file so that it can 
 *            be passed as a parameter to insert function
 *            (allows for each word in each file to be hashed into the table)
 * arguments: string reference to var filename
 * returns:   none
 */
void ht::file_parse(string &filename) 
{ 
    //open an input stream
    ifstream instream;
        
    //check to make sure the file can be opened
    open_or_die(instream, filename);

    // cout << "----" << filename << "----" << endl;

    //an attempt at stopping the file_parse from repeating files
    // if (stopHash == true) {
    //     instream.close();
    //     return;
    // }

    string input;
    int lineNum = 1;
    
    while (getline(instream, input)) {
        // cout << input << endl;
        istringstream ss(input);
        string word;
        string newWord;


        vector<string> line;
        line.resize(0);


        while (ss >> word) {
            // cout << "word is: " << word << endl;
            newWord = stripNonAlphaNum(word);
            // cout << "processed word is: " << newWord << endl;
            bool duplicate = false;

            for (unsigned long int i = 0; i < line.size(); i++) {
                if (line.at(i) == newWord) {
                    duplicate = true;
                }
            }
            line.push_back(newWord);


            if ((newWord != "") and (duplicate == false)) { 
                insert(newWord, filename, lineNum);
            }   
        }
        // cout << endl;
        lineNum++;
    }

    // cout << endl;
    instream.close();
}

/*
 * name:      treeTraversal
 * purpose:   stores the full path of each file in the tree
 *            and passes the filename as a parameter to function file_parse() 
 * arguments: pointer to DirNode, vector of pointers to DirNode, string ref
 *            filename
 * returns:   none
 */
void ht::treeTraversal(DirNode *node, std::vector<DirNode*> 
&filePath, std::string &fileName) {

    if (node == nullptr) {
        return;
    } 
    else {
        filePath.push_back(node); 
    }
    if (node -> hasSubDir()) {
        for (int i = 0; i < node -> numSubDirs(); i++) {
            treeTraversal(node -> getSubDir(i), filePath, fileName);
        }
    }
    if (node -> hasFiles()) {
            for (int i = 0; i < node -> numFiles(); i++) {
                fileName = filePath[0] -> getName();

                for (unsigned long x = 1; x < filePath.size(); x++) {
                    fileName += "/" + filePath[x] -> getName();
                
            }
            fileName += "/" + node -> getFile(i);

            file_parse(fileName);
            }  
    }
    filePath.pop_back();
}

/*
 * name:      search
 * purpose:   case sensitive search for a given word in the files
 * arguments: string var "word", ostream reference to var output
 * returns:   none
 */
void ht::search(string word, ostream &output)
{
    string strippedWord = stripNonAlphaNum(word);
    string lowerCaseWord = lowerCase(strippedWord);
    int hashNum = compressed_hash(lowerCaseWord);
    int bucketNum = caseBucketCheck(hashNum, strippedWord);
    if (bucketNum != -1) {
        printCaseSens(bucketNum, strippedWord, output);
    } else {
        output << strippedWord << " Not Found. Try with @insensitive or @i.\n";
    }
}


int ht::caseBucketCheck(int hashNum, string key)
{
    for (unsigned long int i = hashNum; i < hashTable.size(); i++) {
        if (!hashTable.at(i).isEmpty()) {
            if ((lowerCase(hashTable.at(i).keyAt(0)) == (lowerCase(key)))) {
                for (int j = 0; j < hashTable.at(i).size(); j++) {
                    if (hashTable.at(i).keyAt(j) == key) {
                        return i;
                    }
                }
            }
        } else {
            return -1;
        }
    }
    return -1; 
}

/*
 * name:      printCaseSens
 * purpose:   printing format for sensitive case
 * arguments: int bucket, string var key, ostream reference to var output
 * returns:   none
 */
void ht::printCaseSens(int bucket, string key, ostream &output) {
    ifstream file;
    string lineContent;
    for (int i = 0; i < hashTable.at(bucket).size(); i++) {
        if (hashTable.at(bucket).keyAt(i) == key) {
            file.open(hashTable.at(bucket).fileNameAt(i));
            if (not file.is_open()) {
                cerr << "Unable to read " << hashTable.at(bucket).fileNameAt(i)
                << endl;
            } 
            int loop = hashTable.at(bucket).lineNumAt(i);
            while (loop > 0) {
                getline(file, lineContent);
                loop--;
            }
            output << hashTable.at(bucket).fileNameAt(i) << ":" 
            << hashTable.at(bucket).lineNumAt(i) << ": "
            << lineContent << endl;
            file.close();
        }
    }
}

/*
 * name:      printCaseInsen
 * purpose:   printing format for insensitive case
 * arguments: int bucket, ostream reference to var output
 * returns:   none
 */
void ht::printCaseInsens(int bucket, ostream &output) {
    ifstream file;
    string lineContent;
    for (int i = 0; i < hashTable.at(bucket).size(); i++) {
        file.open(hashTable.at(bucket).fileNameAt(i));
        if (not file.is_open()) {
            cerr << "Unable to read " << hashTable.at(bucket).fileNameAt(i)
            << endl;
        } 
        int loop = hashTable.at(bucket).lineNumAt(i);
        while (loop > 0) {
            getline(file, lineContent);
            loop--;
        }
        output << hashTable.at(bucket).fileNameAt(i) << ":" 
        << hashTable.at(bucket).lineNumAt(i) << ": "
        << lineContent << endl;
        file.close();
    }
}

/*
 * name:      insensitiveSearch
 * purpose:   case insensitive search for a given word in the files
 * arguments: string var "word", ostream reference to var output
 * returns:   none
 */
void ht::insensitiveSearch(string word, ostream &output)
{
    string strippedWord = stripNonAlphaNum(word);
    string lowerCaseWord = lowerCase(strippedWord);
    int hashNum = compressed_hash(lowerCaseWord);
    int bucketNum = insensitiveBucketCheck(hashNum, strippedWord);
    if (bucketNum != -1) {
        printCaseInsens(bucketNum, output);
    } else {
        output << strippedWord << " Not Found.\n";
    }
}


int ht::insensitiveBucketCheck(int hashNum, string key)
{
    for (unsigned long int i = hashNum; i < hashTable.size(); i++) {
        if (!hashTable.at(i).isEmpty()) {
            if ((lowerCase(hashTable.at(i).keyAt(0)) == (lowerCase(key)))) {
                return i;
            }
        } else {
            return -1;
        }
    }
    return -1;
}

/*
 * name:      command_loop
 * purpose:   interface for user/file input to interact with, deals with
 *            different user inputs 
 * arguments: istream reference to variable input, 
 *            ofstream reference to var output
 * returns:   none
 */
void ht::command_loop(istream &input, ofstream &output) {
    string cmd1, cmd2;
    bool end = false;
    while ((not end) and (not input.eof())) {
        cout << "Query? ";
        input >> cmd1;
        // cout << cmd1;
        if (cmd1 == "@q" or cmd1 == "@quit") {
            cout << "Goodbye! Thank you and have a nice day." << endl;
            end = true;
            output.close();
            return;
        } else if (cmd1 == "@i" or cmd1 == "@insensitive") {
            input >> cmd2;
            insensitiveSearch(cmd2, output);

        } else if (cmd1 == "@f") {
            input >> cmd2;
            output.close();
            ofstream outstream;
            open_or_die(outstream, cmd2);
            command_loop(cin, outstream);
            end = true;
            // close current file
            // future output written to new file specified by cmd2
        } else {
            search(cmd1, output);
        }

    }
    cout << "Query? ";
    cout << "Goodbye! Thank you and have a nice day." << endl;
    output.close();
    
}