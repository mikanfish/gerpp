/*
 *  main.cpp
 *  Gabby Fischberg, Nathan Moreno
 *  4/30/2023
 *
 *  CS 15 Proj4
 *
 *  Purpose: driver for gerp, runs gerp to index and respond to queries. 
 *
 */

#include "gerp.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {  
        cerr << "Usage: ./gerp inputDirectory outputFile";
        cerr << endl;
        exit(EXIT_FAILURE); 
    } 

    Gerp gerp(argv[1], argv[2]);
    gerp.run();

    return 0; 
}