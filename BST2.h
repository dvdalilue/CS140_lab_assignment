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
  //Nested Class iterator for "bst"
  class iterator {
  
  public:
    // Public constructors
    iterator() { p=NULL; }
    // Operators definition and overloading
    bool operator==(iterator i) { return (i == p); } // Equivalence
    bool operator!=(iterator i) { return (!(i == p)); } // Inequivalence
    TKey operator*()
    {
        if (p == NULL)
            return NULL;
        return p->key;
    }
    // As the node can not be accessed by a non-member, i can send my own node to 
    // another that can access to TKey.
    bool operator==(node *t)
    {
        if ((t == NULL) && (p == NULL)) return true;
        if ((t == NULL) || (p == NULL)) return false;
        return (t->key == p->key);
    }
    void operator++()
    {
        if (p->link[1]) // Check for a right tree
        {
            p = p->link[1]; 
            while (p->link[0])
            {
                // Search for the min in this tree (right)
                v.push_back(p);
                p = p->link[0];
            }
        }
        else if (!v.empty())
        {
            // If there is no right tree and the stack is not empty, the top is my father
            p = v.back();
            v.pop_back();
        } else { p = NULL; }
    }
  private:
    // Private constructors
    iterator(node *n) { p=n; }
    iterator(node *n, vector<node*> q) { p=n; v=q; }
    friend class bst<TKey>;
    vector<node*> v; // Vector for operator++.
    node *p;
  };

  // Construct a iterator with a pointer to the minimum, and the stack gathered
  iterator begin()
  {
    node *p;
    vector<node*> aux;
    if (Troot)
    {
      p = Troot;
      while (p->link[0])
      {
          aux.push_back(p);
          p = p->link[0];
      }            
      return iterator(p, aux);
    } else {
      return NULL;
    }

  }
  iterator end() { return iterator(); }

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
