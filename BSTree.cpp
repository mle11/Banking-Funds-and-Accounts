#include "BSTree.h"


BSTree::BSTree() {
}
    
bool BSTree::Insert(Account* account) {
    if (account->getAccountID() < 100 || account->getAccountID() > 9999) {
        cerr << "ERROR: Account Number Not Valid " << account->getAccountID() << endl;
        return false;
    } else{
        return InsertRecursive(account, root_);
    }
    return false;
}

bool BSTree::Retrieve(int accountID, Account*& account) const {
    return RetrieveRecursive(accountID, account, root_);
}

void BSTree::Display() const {
    if (isEmpty()) {
        cerr << "ERROR: ACCOUNT LIST IS EMPTY" << endl;
    }
    DisplayRecursive(root_);
}

void BSTree::Empty() {
    delete root_;
    root_ = nullptr;
    return;
}

bool BSTree::isEmpty() const {
    return (root_->left == nullptr && root_->right == nullptr);
}

bool BSTree::InsertRecursive(Account* account, Node*& root) {
    if (root == nullptr){
        root = new Node;
        root->acct = account;
        root->left = nullptr;
        root->right = nullptr;
        return true;
    }
    int accountID = root->acct->getAccountID();
    if (account->getAccountID() > accountID) {
        InsertRecursive(account, root->right);
    } else if (account->getAccountID() < accountID) {
        InsertRecursive(account, root->left);
    } else {
        cerr << "ERROR: Account " << account->getAccountID() << " is already open. Transaction refused." << endl;
    }
    return false;
}

bool BSTree::RetrieveRecursive(int accountID, Account*& account, Node* root) const {
    if (root != nullptr) {
        if (accountID == root->acct->getAccountID()) {
            account = root->acct;
            return true;
        }
        if (accountID < root->acct->getAccountID()) {
            return RetrieveRecursive(accountID, account, root->left);
        } else {
            return RetrieveRecursive(accountID, account, root->right);
        }
    } else {
        cerr << "ERROR: Account " << accountID << " not found. Transferal refused." << endl;
        return false;
    }
}

void BSTree::DisplayRecursive(Node* root) const {
    if (root == nullptr) {
        return;
    }
    DisplayRecursive(root->left);
    cout << *root->acct;
    DisplayRecursive(root->right);
}

ostream& operator<<(ostream& stream, const BSTree& tree) {
    tree.Display();
    return stream;
}

BSTree::~BSTree() {
    Empty();
}