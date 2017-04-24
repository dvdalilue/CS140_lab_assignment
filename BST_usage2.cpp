#include <cstdlib>
#include <fstream>
#include <iostream>
#include "BST2.h"

using namespace std;

template <typename Iterator>
void print(Iterator i0, Iterator i1)
{
  while (i0 != i1) {
    cout << " " << *i0;
    ++i0;
  }
  cout << "\n";
}

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

  //T.print_bylevel();

  print(T.begin(), T.end());

  while (!T.empty()) {
    cout << "Erase [key]: ";
    cin >> key;
    if (cin.eof())
      break;

    T.erase(key);
    print(T.begin(), T.end());
  }

  cout << "\n";
}
