#ifndef FUND_H_
#define FUND_H_
#include "Transaction.h"
#include <string>
#include <vector>
#include <iostream>

class Fund {
public:
	Fund();

	int getBalance() const;
	string getName() const;

	void setName(string name);

	bool Add (int amount);
	bool Subtract(int amount);
	bool Balance(int amount);
	bool Record(Transaction trans);
	void PrintHistory();
	void PrintFundHistory();

private:
	string fund_;
	int balance_ = 0;
	vector<Transaction> history_;
};
#endif