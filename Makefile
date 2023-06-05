/*
 *  Makefile
 *  Isaac Monheit and Kabir Pamnani
 *  Spring 2022
 *
 *  CS 15 proj3 
 *
 *  This file contains all the compilation and linking commands that allows 
 *  my program to be run correctly. It simplifies the users life so they 
 *  don't have to manually compile all the files everytime they want to 
 *  run it. It makes the work more efficient.
 *
 */


MAKEFLAGS += -L 

CXX      = /usr/sup/bin/clang++
CXXFLAGS = -g3 -ggdb -O3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3

stringProcessing.o: stringProcessing.cpp stringProcessing.h
	$(CXX) $(CXXFLAGS) -c $<

FSTreeTraversal.o: FSTreeTraversal.cpp FSTree.h DirNode.h ht.h
	$(CXX) $(CXXFLAGS) -c $<

Bucket.o: Bucket.cpp Bucket.h fileStruct.h
	$(CXX) $(CXXFLAGS) -c $<

ht.o: ht.cpp ht.h FSTree.h DirNode.h stringProcessing.h fileStruct.h  Bucket.h
	$(CXX) $(CXXFLAGS) -c $<

testing_main.o: testing_main.cpp FSTree.h DirNode.h fileStruct.h Bucket.h
	$(CXX) $(CXXFLAGS) -c $<

# FSTree.o: FSTree.cpp FSTree.h
# 	$(CXX) $(CXXFLAGS) -c FSTree.cpp

# DirNode.o: DirNode.cpp DirNode.h
# 	$(CXX) $(CXXFLAGS) -c DirNode.cpp

treeTraversal: FSTreeTraversal.o FSTree.o DirNode.o ht.o
	$(CXX) $(LDFLAGS) -o $@ $^

gerp: testing_main.o ht.o FSTree.o DirNode.o stringProcessing.o Bucket.o
	$(CXX) $(LDFLAGS) -o $@ $^

string: stringProcessing.o	
	$(CXX) $(LDFLAGS) -o $@ $^

