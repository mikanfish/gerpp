MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

gerp: main.o HashNode.o HashTable.o Gerp.o DirNode.o FSTree.o
	$(CXX) $(CXXFLAGS) -o gerp $^

FSTreeTraversal.o: FSTreeTraversal.cpp FSTree.h DirNode.h
	$(CXX) $(CXXFLAGS) -c FSTreeTraversal.cpp 

treeTraverse: FSTreeTraversal.o FSTree.o DirNode.o
	$(CXX) -o treeTraverse FSTreeTraversal.o FSTree.o DirNode.o

HashTable.o: HashTable.h
	$(CXX) $(CXXFLAGS) -x c++ -c HashTable.h -o HashTable.o

HashNode.o: HashNode.h
	$(CXX) $(CXXFLAGS) -x c++ -c HashNode.h -o HashNode.o

Gerp.o: gerp.h gerp.cpp FSTree.h DirNode.h HashTable.h HashNode.h
	$(CXX) $(CXXFLAGS) -c gerp.cpp -o Gerp.o

main.o: main.cpp Gerp.o
	$(CXX) $(CXXFLAGS) -c main.cpp

unit_test: unit_test_driver.o HashNode.o Gerp.o DirNode.o FSTree.o
	$(CXX) $(CXXFLAGS) unit_test_driver.o HashNode.o Gerp.o DirNode.o FSTree.o

provide:
	provide comp15 proj4_gerp README Makefile gerp.cpp gerp.h \
			HashNode.h HashTable.h main.cpp unit_tests.h \
