/*
 *  gerp.cpp
 *  Gabby Fischberg, Nathan Moreno
 *  4/30/2023
 *
 *  CS 15 Proj4
 *
 *  Purpose: Implementation of a gerp class that uses HashTable to index 
 *          files and responds to queries on the contents of files
 *
 */

#include <string>
#include <iostream>
#include <sstream>
#include "gerp.h"
#include "DirNode.h"

using namespace std;
/*
 * name:      constructor
 * purpose:   creates an instance of gerp and initializes private variables
 * arguments: strings representing name of directory and output file
 * returns:   none
 * effects:   creates gerp
 */
Gerp::Gerp(string directory, string output_filename){
    outputfile = output_filename; 
    directory_name = directory; 
    make_ofstream(outputfile); 
}
/*
 * name:      run
 * purpose:   runs gerp
 * arguments: none
 * returns:   none
 * effects:   none
 */
void Gerp::run() {
    index();
    query();
}
/*
 * name:      index
 * purpose:   indexes contents of file into hash tables
 * arguments: none
 * returns:   none
 * effects:   indexes into hash tables
 */
void Gerp::index() {
    FSTree tree = FSTree(directory_name);
    DirNode *root = tree.getRoot();
    traverse(root, "");
}
/*
 * name:      make_ofstream
 * purpose:   opens an outstream given a file
 * arguments: string output_filename
 * returns:   none
 * effects:   creates outstream
 */
void Gerp::make_ofstream(string output_filename) {
    //close any open stream before opening a new one
    if (outstream.is_open()) {
        outstream.close();
    } 

    outstream.open(output_filename);
}
/*
 * name:      query
 * purpose:   handles query loop for inputting commands
 * arguments: none
 * returns:   none
 * effects:   none
 */
void Gerp::query() {
    bool shouldcont = true; 
    //prompts user for input and runs command corresponding to input
    while (shouldcont){
        cout << "Query? ";
        string input;
        cin >> input; 
        
        if (input == "@q" or input == "@quit") {
            shouldcont = false; 
            cout << "Goodbye! Thank you and have a nice day.\n";
        } else if (input == "@i" or input == "@insensitive") {
            cin >> input;
            input = stripNonAlphaNum(input); 
            inSearch(input);
        } else if (input == "@f") {
            cin >> input;
            make_ofstream(input);
        } else {
            input = stripNonAlphaNum(input); 
            search(input);
        }
    }
}

/*
 * name:      readfile
 * purpose:   reads from file, indexes words into hash table
 * arguments: string &pathname, ifstream &filepath
 * returns:   none
 * effects:   indexes into hash tables
 */
void Gerp::readfile(string &pathname, ifstream &filepath) {
    string pathline, line, word;
    int linenumber = 0; 
    // indexes each line and each word into appropriate hashTable
    while (getline(filepath, line)){
        linenumber++; 
        pathline = pathname + ":" + to_string(linenumber);
        auxInsert(pathline, line);
        // god doesnt play with dice, but we do.
        HashTable<std::string, bool> temp; 
        stringstream ss(line);
        while (ss >> word) {
            word = stripNonAlphaNum(word);
            if (temp.contains(word)){
                continue;
            } else {
                readFileHelper(word, pathline, temp);
            }
        }
    }
}

/*
 * name:      readFileHelper
 * purpose:   inserts non-duplicate words into the hash tables
 * arguments: Strings representing word to insert and path with line number and 
 *            reference to a temporary hashtable for checking duplicates
 * returns:   none
 * effects:   words indexed into hashtables
 */
void Gerp::readFileHelper(const string &word, const string &pathline, 
                          HashTable<std::string, bool> &temp) {
    bool tt = true;
    int wordlength;
    string lowerword = ""; 

    temp.insert(word, tt);
    // if current variation of word has not been indexed, insert to insensitive 
    // hashtable
    if (not words.contains(word)) {
        wordlength = word.length();
        char c;
        lowerword = word;
        // create fully lowercase version of word
        for (int i = 0; i < wordlength; i++) {
            c = tolower(word[i]); 
            lowerword[i] =  c; 
        }
        insensitiveInsert(lowerword, word);
        lowerword = "";
    } 
    wordInsert(word, pathline); 
}

/*
 * name:      traverse
 * purpose:   traverses file, reads from file 
 * arguments: DirNode *node, string path
 * returns:   none
 * effects:   none
 */
void Gerp::traverse(DirNode *node, string path) {
    path += node->getName() + "/";

    string file;
    int num_files = node->numFiles();
    // read each file in FSTree
    for (int i = 0; i < num_files; i++) {
        file = path + node->getFile(i);

        ifstream filestream;
        attempt_open(filestream, file);

        readfile(file, filestream); 
        filestream.close();
    }

    int num_sub = node->numSubDirs();
    for (int i = 0; i < num_sub; i++) {
        DirNode *curr = node->getSubDir(i);
        traverse(curr, path);
    }
}
/*
 * name:      wordInsert
 * purpose:   inserts value into vector of key for word hash
 * arguments: string key, string value
 * returns:   none
 * effects:   inserts into word hash table
 */
void Gerp::wordInsert(string key, string value) {
    //check if words contains key
    vector<string> *ptr;
    // push back of vector for word if already in hash table
    if (words.contains(key)) {
        ptr = words.getNodeValue(key);
        ptr->push_back(value);
    } else {
        vector<string> new_vector;
        new_vector.push_back(value);
        words.insert(key, new_vector);
    }
}
/*
 * name:      auxInsert
 * purpose:   inserts value of key for aux hash
 * arguments: string key, string value
 * returns:   none
 * effects:   inserts into aux hash table
 */
void Gerp::auxInsert(string key, string value) {
    aux.insert(key, value);
}
/*
 * name:      insensitiveInsert
 * purpose:   inserts value into vector of key for insensitive hash
 * arguments: string key, string value
 * returns:   none
 * effects:   inserts into insensitive hash table
 */
void Gerp::insensitiveInsert(string key, string value) {
    vector<string> *ptr;
    if (insensitive.contains(key)) {
        ptr = insensitive.getNodeValue(key);
        ptr->push_back(value);
    } else {
        vector<string> new_vector;
        new_vector.push_back(value);
        insensitive.insert(key, new_vector);
    }
}

/*
 * name:      search
 * purpose:   case sensitive search in word hash
 * arguments: string key
 * returns:   none
 * effects:   prints to outstream if word is found or not
 */
void Gerp::search(string key) {
    //check if word is contained in key and print path
    if (words.contains(key) and key != ""){
        vector<string> *ptr = words.getNodeValue(key);
        string path; 
        int instances = ptr->size();
        for (int i = 0; i < instances; i++){
            path = ptr->at(i);
            print(path);
        }
        return;
    }
    outstream << key << " Not Found. Try with @insensitive or @i." << endl;
}
/*
 * name:      inSearchHelper
 * purpose:   helps print out lines only once for insensitive search 
 * arguments: string key, HashTable<std::string, bool> &buffer
 * returns:   none
 * effects:   stores lines in temporary hash to check if its been printed
 */
void Gerp::inSearchHelper(string key, HashTable<std::string, bool> &buffer) {
    bool tt = true;
    vector<string> *ptr = words.getNodeValue(key);
    string path; 
    int instances = ptr->size();
    for (int i = 0; i < instances; i++){
        path = ptr->at(i);
        // ensures duplicates are not printed
        if (not buffer.contains(path)){
            buffer.insert(path, tt);
            print(path);
        } 
    }
}
/*
 * name:      inSearch
 * purpose:   case insensitive search in word hash
 * arguments: string key
 * returns:   none
 * effects:   prints to outstream if word is found or not
 */
void Gerp::inSearch(string key) {
    if (insensitive.contains(key) and key != ""){
        vector<string> *ptr = insensitive.getNodeValue(key);
        HashTable<std::string, bool> buffer; 
        int numwords = ptr->size();
        string permutation, path; 
        for (int i = 0; i < numwords; i++){
            permutation = ptr->at(i);
            //search words for that permutation
            inSearchHelper(permutation, buffer);
        }
    } else {
        outstream << key << " Not Found.\n";
    }
}
/*
 * name:      changeOutput
 * purpose:   changes output to new_file_name
 * arguments: string key
 * returns:   none
 * effects:   prints to outstream if word is found or not
 */
void Gerp::changeOutput(string new_file_name) {
    make_ofstream(new_file_name);
}
/*
 * name:      attempt_open
 * purpose:   attempts to open file_name
 * arguments: ifstream &stream, string file_name
 * returns:   none
 * effects:   throws error if unable to open
 */
void Gerp::attempt_open(ifstream &stream, string file_name) {
    stream.open(file_name);
    if (!stream.is_open()) {
        abort("Unable to open file" + file_name);
    }
} 
/*
 * name:      abort
 * purpose:   throws error message
 * arguments: string error_message
 * returns:   none
 * effects:   throws error
 */
void Gerp::abort(string error_message) {
    throw std::runtime_error(error_message);
    exit(EXIT_FAILURE);
}
/*
 * name:      print
 * purpose:   prints pathname and line number
 * arguments: ifstream &stream, string file_name
 * returns:   none
 * effects:   prints to outstream
 */
void Gerp::print(string &pathname) {
    string *line = aux.getNodeValue(pathname);
    outstream << pathname << ": " << *line << endl; 
}
/*
 * name:      stripNonAlphaNum
 * purpose:   strips all leading and ending non alpha numerical chars
 * arguments: string input
 * returns:   stripped string
 * effects:   none
 */
string Gerp::stripNonAlphaNum (string input){
    int start = 0; 
    int length = input.length();
    while (start < length and not isalnum(input[start])){
        start++; 
    }
    int end = input.length() - 1; 
    while (end > 0 and not isalnum(input[end])){
        end--; 
    }
    int len = end - start + 1; 
    if (start <= end){
        return input.substr(start, len); 
    }
    
    return ""; 
}
