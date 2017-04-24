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
        node() { key=TKey(); parent=link[0]=link[1]=NULL; }
        void print();
    
        TKey key;
        node *parent;
        node *link[2];
    };

public:
    bst()  { Troot=NULL; }
    ~bst() { clear(Troot); }

    bool empty() { return Troot==NULL; }

    void insert(TKey &);
    void erase(TKey &);
    void print_bylevel();

private:
    void clear(node *);
    node *minmax_key(node *, int);
    node *insert(node *, node *, TKey &); // New function that recieve the node father.
    node *insert(node *, TKey &);
    node *erase(node *, TKey &);

    node *Troot;
};

// Function that prints it self, the father, left son and rigth son
template <class TKey>
void bst<TKey>::node::print()
{
    cout << setw(3) << key << " :";

    if (parent != NULL) cout << " P=" << setw(3) << parent->key;
    else                cout << " P= NA";
    if (link[0])        cout << " L=" << setw(3) << link[0]->key;
    else                cout << "      ";
    if (link[1])        cout << " R=" << setw(3) << link[1]->key;
    else                cout << "      ";

    cout << "\n";
}

// Function that delete every node in the tree.
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
  Troot = insert(Troot, NULL, key);
}

// Function that insert a new TKey in Troot, if it doesn't exist. linking with its parent.
template <class TKey>
class bst<TKey>::node *bst<TKey>::insert(node *T, node *p, TKey &key)
{
  if (T == NULL) {
    T = new node;
    T->key = key;
    T->parent = p;
  } else if (T->key == key) {
    ;
  } else {
    int dir = T->key < key;
    T->link[dir] = insert(T->link[dir], T, key);
  }

  return T;
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

template <class TKey>
void bst<TKey>::erase(TKey &key)
{ 
  Troot = erase(Troot, key);
}

// Modification: When a TKey is remove, the tree changes its structure. And the node
// that takes his place will have a new father (node)
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
      T->parent = Tm->parent;
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
