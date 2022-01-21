#ifndef BSTree_h
#define BSTree_h
#include "Account.h"
#include <stdio.h>
#include <iostream>
using namespace std;

class BSTree {
friend ostream& operator<<(ostream &out, const BSTree& tree);
public:
    BSTree();
 
    bool Insert(Account* p_account);
    bool Retrieve(int acct_ID, Account*& p_account) const;
    void Display() const;
    void Empty();
    bool isEmpty() const;

    ~BSTree();

private:
    struct Node{
        Account* acct;
        Node* right;
        Node* left;
    };
    Node* root_ = nullptr;
    bool InsertRecursive(Account* p_account, Node*& root);
    bool RetrieveRecursive(int acct_ID, Account*& p_account, Node* root) const;
    void DisplayRecursive(Node* root) const;
};



#endif