/*
 * Author: Kabir Pamnani
 * Date: 04/11/2022
 * File Purpose: When executed, this program should take the highest directory 
 * as a command line argument, and then print the full paths of
 * all the files accessible from that directory
 */

 #include "FSTree.h"
 #include "DirNode.h"
 #include "ht.h"
 #include <vector>
 #include <iostream>

void treeTraversal(DirNode *node, std::vector<DirNode*> &filePath, std::string fileName);

using namespace std;

int main(int argc, char* argv[])
{   
    if (argc != 2) {
        return 1;
    }

    std::string dir = argv[1];

    FSTree fs_tree(dir);

    std::vector<DirNode*> filePath;

    treeTraversal(fs_tree.getRoot(), filePath, "");

    return 0;
}

void treeTraversal(DirNode *node, std::vector<DirNode*> &filePath, std::string fileName) {
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
            fileName += filePath[0] -> getName();

            for (unsigned long x = 1; x < filePath.size(); x++) {
                fileName += "/" + filePath[x] -> getName();
            }
            fileName += "/" + node -> getFile(i);
            
        }
        std::cout << fileName;
       
        // test.file_parse(fileName);
    }
    filePath.pop_back();
}
