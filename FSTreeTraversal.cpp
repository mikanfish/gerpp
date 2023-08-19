#include "FSTree.h"
#include "DirNode.h"
#include <iostream>
#include <string>

using namespace std;

void traverse(DirNode *node, string path);

int main(int argc, char *argv[]) {
  if (not (argc == 2)) {
    cerr << "ur mom\n";
    exit(EXIT_FAILURE);
  }
  
  FSTree tree = FSTree(argv[1]);
  DirNode *root = tree.getRoot();

  traverse(root, "");

  return 0;
}

void traverse(DirNode *node, string path) {
  path += node->getName() + "/";

  int num_files = node->numFiles();
  for (int i = 0; i < num_files; i++) {
    cout << path << node->getFile(i) << "\n";
  }

  int num_sub = node->numSubDirs();
  for (int i = 0; i < num_sub; i++) {
    DirNode *curr = node->getSubDir(i);
    traverse(curr, path);
  }
}