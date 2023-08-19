#include "stringProcessing.h"
using namespace std; 
string stripNonAlphaNum (string input){
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
    if(start <= end){
        return input.substr(start, len); 
    } else {
        return ""; 
    }
}



