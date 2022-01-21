#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include "Transaction.h"
#include "Fund.h"
#include <iostream>
#include <string>
using namespace std;

class Account {
	friend ostream& operator<< (ostream& stream, Account& account);

public:
	Account();
	Account(string first, string last, int accountID);

	int getAccountID() const;
	int getBalance(int fundID) const;
	string getFundName(int fundID);
	string getFirst() const;
	string getLast() const;

	void setFundID(int fundID);

	void AddFunds(int fundID, int amount);
	void RemoveFunds(int primaryFund, int secondaryFund, int amount);
	bool RemoveJointFunds(int fundID, int amount, Transaction transaction);
	void Record(Transaction transaction, int fundID);
	void PrintHistory();
	void PrintFundHistory(int fundID);
	void Error(int amount, string firstName, string lastName, int fundID);

private:
	string first_;
	string last_;
	int accountID_;
	int fundID_;
	Fund funds[8];
};
#endif