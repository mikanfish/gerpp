/*
 *  gerp.h
 *  Gabby Fischberg, Nathan Moreno
 *  4/30/2023
 *
 *  CS 15 Proj4
 *
 *  Purpose: Interface for gerp class, includes relevant functions
 *      such as reading from file, indexing, and searching HashTables
 *
 */

#ifndef GERP_H
#define GERP_H

#include "FSTree.h"
#include "DirNode.h"
#include "HashTable.h"
#include "HashNode.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

class Gerp {
    public:
    Gerp(std::string directory, std::string output_filename);
    void run();

    private: 
    void readfile(std::string &pathname, std::ifstream &filepath);
    void readFileHelper(const string &word, const string &pathline,             
                        HashTable<std::string, bool> &temp);

    void traverse(DirNode *node, std::string path);
    //our hashtables
    HashTable<std::string, std::vector<std::string>> words;
    HashTable<std::string, std::string> aux; //key: path/line num; value: line
    HashTable<std::string, std::vector<std::string>> insensitive; 
                    //key: lower case word, value = permutations of word

    std::string outputfile; 
    std::string directory_name;
    std::ofstream outstream;

    void index();
    void make_ofstream(std::string output_filename);
    void query();

    void wordInsert(std::string key, std::string value);
    void auxInsert(std::string key, std::string value);
    void insensitiveInsert(std::string key, std::string value);

    void search(std::string key);
    void inSearch(std::string key);
    void inSearchHelper(string key,  HashTable<std::string, bool> &buffer);

    void changeOutput(std::string new_file_name);

    std::string stripNonAlphaNum (std::string input);
    void attempt_open(std::ifstream &stream, std::string file_name);
    void abort(std::string error_message);
    void print(std::string &pathname);
};

#endif