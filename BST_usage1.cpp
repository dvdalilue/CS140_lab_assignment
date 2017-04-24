#include <cstdlib>
#include <fstream>
#include <iostream>
#include "BST1.h"
using namespace std;

int main(int argc, char *argv[])
{
  if (argc != 2) {
    cerr << "usage: bst1 datafile\n";
	exit(0);
  } 

  int key;
  bst<int> T;

  ifstream fin(argv[1]);

  while (fin >> key)
    T.insert(key);

  fin.close();

  T.print_bylevel();
}
