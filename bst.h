#ifndef BST_H
#define BST_H

#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <class TKey>
class bst {
  struct node {
    node() { key=TKey(); link[0]=link[1]=NULL; }
	void print();

    TKey key;
    node *link[2];
  };
  
  public:
	class iterator {
	  public:
		default constructor (no argument)
		overloaded operators (++, *, ==, !=)
	  private:
	    friend class bst<TKey>;
		constructor (with argument)

	    node *p;
	};

	iterator begin() { ... }
	iterator end() { ... }

  public:
    bst() { Troot=NULL; }
	~bst() { clear(Troot); }

	bool empty() { return Troot==NULL; }

	void insert(TKey &);
	void erase(TKey &);

	iterator lower_bound(const TKey &);
	iterator upper_bound(const TKey &);
	void erase(iterator, iterator);

	void print_bylevel();

  private:
	void clear(node *);
	node *minmax_key(node *, int);
	node *insert(node *, TKey &);
	node *erase(node *, TKey &);

    node *Troot;
};

template <class TKey>
void bst<TKey>::node::print()
{
  cout << setw(3) << key << " :";

  if (link[0]) cout << " L=" << setw(3) << link[0]->key;
  else         cout << "      ";
  if (link[1]) cout << " R=" << setw(3) << link[1]->key;
  else         cout << "      ";

  cout << "\n";
}

bst<TKey>::iterator functions not defined above go here


template <class TKey>
void bst<TKey>::clear(node *T)
{
  if (T) {
    clear(T->link[0]);
    clear(T->link[1]);
    delete T;
    T = NULL;
  }
}

template <class TKey>
class bst<TKey>::node *bst<TKey>::minmax_key(node *T, int dir)
{
  if (T) {
    while (T->link[dir])
      T = T->link[dir];
  }

  return T;
}

template <class TKey>
void bst<TKey>::insert(TKey &key)
{ 
  Troot = insert(Troot, key);
}

template <class TKey>
class bst<TKey>::node *bst<TKey>::insert(node *T, TKey &key)
{
  if (T == NULL) {
    T = new node;
    T->key = key;
  } else if (T->key == key) {
    ;
  } else {
    int dir = T->key < key;
    T->link[dir] = insert(T->link[dir], key);
  }

  return T;
}

bst<TKey>::lower_bound function goes here

bst<TKey>::upper_bound function goes here

template <class TKey>
void bst<TKey>::erase(TKey &key)
{ 
  Troot = erase(Troot, key);
}

new bst<TKey>::erase function goes here

template <class TKey>
class bst<TKey>::node *bst<TKey>::erase(node *T, TKey &key)
{
  node *Tm;

  if (T == NULL) {
    ;
  } else if (T->key == key) {
    if (T->link[0] && T->link[1]) {
      Tm = minmax_key(T->link[0], 1);
      T->key = Tm->key;
      T->link[0] = erase(T->link[0], T->key);
    } else {
      Tm = T;
      if      (T->link[0]) T=T->link[0];
      else if (T->link[1]) T=T->link[1]; 
      else                 T=NULL;
      delete Tm;
    }
  } else {
    int dir = T->key < key;
    T->link[dir] = erase(T->link[dir], key);
  }

  return T;
}

template <class TKey>
void bst<TKey>::print_bylevel()
{
  if (Troot == NULL)
    return;

  queue<node *> Q;
  node *T;

  Q.push(Troot);
  while (!Q.empty()) {
    T = Q.front();
    Q.pop();

    T->print();
    if (T->link[0]) Q.push(T->link[0]);
    if (T->link[1]) Q.push(T->link[1]);
  }
}
#endif
