#pragma once
#include<queue>
#include"BSTree.h"
#include"Transaction.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>

using namespace std;

class Bank 
{
public:
	Bank();
	bool ReadTransactions(string fileName);
	void Process();
	void Display();

private:
	queue<Transaction> transactionList;
	BSTree accountList;

};