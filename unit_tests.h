#include "HashNode.h"
#include "HashTable.h"
#include "gerp.h"
#include <cassert>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
using namespace std; 

// tests if class is defined correctly 
// void dummytest() {
//     std::cout << "things are running";
//     assert(true);
// }

// void hashnode_empty() {
//     HashNode<char, char> node; 
// }

// void notemptyhashnode(){
//     vector<string> myVector;
//     string test = "hello world";
//     HashNode<string, vector<string>> mynode(test, myVector);
// }

// void getkeyandvaluetest(){
//     string test = "hello world";
//     char c = 'c';
//     HashNode<string, char> mynode(test, 'c');
//     cout << "test results\n";

//     assert(mynode.getKey() == "hello world");
//     char cc = *mynode.getValue();
//     assert(cc == c);
// }

// void HashNode_isFull_test(){
//     vector<string> myVector;
//     string test = "hello world";
//     HashNode<string, vector<string>> mynode(test, myVector);

//     assert(mynode.isFull() == true);
// }

// void hashnode_getNext() {
//     HashNode<char, char> node; 

//     assert(node.getNext() == nullptr);
// }

// void hashnode_setNext(){
//     HashNode<string, char> mynode("hello", 'c');
//     HashNode<string, char> nodetwo("cssucks", 'f');
//     HashNode<string, char>* pointy = &nodetwo;
//     mynode.setNext(pointy);
//     assert(mynode.getNext() == pointy);
    
// }

// void hashnode_setValue() {
//     string test = "hello world";
//     char c = 'c';
//     HashNode<string, char> mynode(test, 'c');
//     char cc = *mynode.getValue();
//     assert(cc == c);
//     mynode.setValue('b');
//     char bb = *mynode.getValue();
//     assert(bb == 'b');
// }
// void hashTable_empty(){
//     HashTable<string, char> test;
// }

// //also tests getNodeValue
// void hashTable_insert() {
//     HashTable<string, char> test;
//     test.insert("hello", 'p');

//     char *pointy = test.getNodeValue("hello");
//     assert(*pointy = 'p');
// }


// void hashTable_rehash() {
//     HashTable<string, char> test;
//     //int test_size = test.size;
//     HashNode <string, char> mynode("hello", 'c');  
//     test.table->at(0).next = &mynode;

//     // test.insert("poop", 'p');
//     test.rehash();
// }

// void overloadedop(){
//     HashNode <string, char> mynode("hello", 'c');  
//     HashNode <string, char> empty;
//     empty = mynode; 
//     //cout << empty.key << endl;
//     assert(empty.key == "hello");
// }

// //test contains
// void testcontains(){
//     HashTable<string, char> test;
//     test.insert("hello", 'p');

//     assert(test.contains("hello"));
// }
// //TODO; TEST INSERTING WITH SAME KEY, for gerp class using vectors
// //test collisions
// void hashTable_weird_collision() {
//     HashTable<string, char> test;
//     HashNode <string, char> nodetwo("poop", 'p');  

//     int hello_index = test.getIndex("hello");
//     test.table->insert(test.table->begin() + hello_index, nodetwo);
//     test.insert("hello", 'c');

//     HashNode<string, char> *check = &test.table->at(hello_index);
//     // HashNode<string, char> *next_check = check->next; 
//     string key = check->next->key;
//     string key1 = check->key; 
//     assert(key1 == "poop");
//     assert(key == "hello"); 

//     // cout << check->next->value << "\n";
//     // cout << check->next->key<< "\n";
// }

// void hashTable_collide() {
//     HashTable<string, char> test;
//     //int test_size = test.size;
//     HashNode <string, char> *mynode = new 
//                                     HashNode <string, char> ("hello", 'c'); 
//     HashNode <string, char> *tester = &test.table->at(0);
    
//     if (tester->next == nullptr) {
//         // cout << "1" << endl;
//     }
//     tester->next = mynode; 

// }

// //test inserting a lot
// void hashTable_insert_big() {
//     HashTable<string, int> test;
//     string keyy = ""; 
//     // char hi; 
//     int index;
//     for (int i = 0; i < 100; i++){
//         // hi = i; /
//         // keyy += hi; 

//         keyy += 'a';
//         // keys were previously the same so it was placing them in at the same spot and not rehashing collided nodes.
//         // cout << keyy << " ";
//         test.insert(keyy, i);
//         // cout << test.contains(keyy) << endl; 
//         // index = hash<string>{}(keyy) % test.capacity;
//         // cout << keyy <<  " " << test.contains(keyy) << " " << index << endl;;

//         // cout << endl << "-----------------------------------------------\n";
//         // test.printTable();
//         // cout << endl << "-----------------------------------------------\n\n";
//     }
//     keyy = "";
//     for(int i = 0; i < 100; i++) {
//         keyy += 'a';
//         index = hash<string>{}(keyy) % test.capacity;
//         // cout << keyy <<  " " << test.contains(keyy) << " " << index << endl;;
//     }
//     // cout << endl;
//     // test.printTable();
// }
// //test inserting vecgtor 
// void hashTable_weird_vectorInsert() {
//     HashTable<string, vector<char>> test;
//     vector<char> test_vector;
//     test.insert("poop", test_vector);
// }

// //tests if class is defined correctly 
// void gerpdummytest() {
//     Gerp gerp; 
// }
// //TODO: TEST For large small and weird data 
// //TODO FOR NEXT TIME: UNPRIV

// void gerp_wordinsert(){
//     Gerp gerp; 
//     gerp.wordInsert("key", "value");
//     gerp.wordInsert("key", "valuetwo");
//     std::vector<std::string>* x = gerp.words.getNodeValue("key");
//     string words;
//     int sizee = x->size();
//     // for (int i = 0; i < sizee; i++) {
//     //     words = x->at(i);
//     //     std::cout << words << " ";
//     // }
//     // std::cout << std::endl;
    
// }

// void gerp_auxinsert(){
//     Gerp gerp;
//     gerp.auxInsert("key", "value");
//     assert(gerp.aux.contains("key")); 
// }

// void gerp_insensitiveinsert(){
//     Gerp gerp; 
//     gerp.insensitiveInsert("key", "ivalue");
//     gerp.insensitiveInsert("key", "ivaluetwo");
//     std::vector<std::string>* x = gerp.insensitive.getNodeValue("key");
//     string words;
//     //int sizee = x->size();
// //     for (int i = 0; i < sizee; i++) {
// //         words = x->at(i);
// //         std::cout << words << " ";
// //     }
// //     std::cout << std::endl;
// }

// todo: test traverse and readfile 
// void traversetest(){
//     Gerp gerp;
//     string path = "/comp/15/files/proj4-test-dirs/tinyData";
//     FSTree tree = FSTree(path);
//     DirNode *root = tree.getRoot();
//     gerp.traverse(root, "");
//     gerp.words.printTable();
//     cout << endl;
//     gerp.aux.printTable(); 
//     cout << endl;
//     gerp.insensitive.printTable();
//     cout << endl;

// }

// void readfiletest(){
//     Gerp gerp; 
//     ifstream filestream;
//     string stringy = "story.txt";
//     gerp.attempt_open(filestream, stringy);
//     string story = "/h/nmoren01/cs15/proj4/story.txt";
//     gerp.readfile(story, filestream);
//     // gerp.aux.printTable();
//     // cout << "------------------I WANT TO HAVE A WORD WITH YOU--------------\n";
//     vector<string>* ptr = gerp.insensitive.getNodeValue("butts"); 
//     int sizee = ptr->size(); 
//     for (int i = 0; i < sizee; i++) {
//         cout << ptr->at(i) << " " << endl;
//     }
//     cout << "Poop on me\n";
//     // gerp.words.printTable();
//     // cout << gerp.words.contains("lie") << endl; 
//     // cout << gerp.words.contains("I") << endl; 
//     // cout << "----------------YOURE SO INSENSITIVE-----------------------\n";
//     gerp.insensitive.printTable();
//     // cout << "-----------------------AUX AUX AUX AUX-----------------\n";
//     // gerp.aux.printTable();
    
//     // std::vector<std::string>* x = gerp.words.getNodeValue("big");
//     // string wordss;
//     // int sizee = x->size();
//     // for (int i = 0; i < sizee; i++) {
//     //     wordss = x->at(i);
//     //     std::cout << wordss << " ";
//     // }
//     // std::cout << std::endl;
// }


// void search_print () {
//     Gerp gerp(); 
//     ifstream filestream;
//     string stringy = "story.txt";
//     gerp.attempt_open(filestream, stringy);
//     string story = "/h/nmoren01/cs15/proj4/story.txt";
//     gerp.readfile(story, filestream);
//     gerp.search("butts");
//     gerp.search("urmom.png");
// }

// void insensy_print(){
//     Gerp gerp; 
//     ifstream filestream;
//     string stringy = "story.txt";
//     gerp.attempt_open(filestream, stringy);
//     string story = "/h/nmoren01/cs15/proj4/story.txt";
//     gerp.readfile(story, filestream);
//     gerp.inSearch("butts");
//     gerp.inSearch("urmom.png");
// }

//******** NOTE THAT ALL THE TESTS ABOVE TEST INDIVIDUAL FUNCTIONS AND USE
//                  AN OUTDATED CONSTRUCTOR***********


// void constructy(){
//     string directory = "/comp/15/files/proj4-test-dirs/tinyData";
//     string out = "output.txt";
//     Gerp gerp(directory, out);
// }

//TODO: make private variables in hash classes

void small_directory() {
    string directory = "/comp/15/files/proj4-test-dirs/tinyData";
    string out = "output.txt";
    Gerp gerp(directory, out);
    gerp.run();
    gerp.words.printTable();
}