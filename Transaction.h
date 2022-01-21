#ifndef TRANSACTION_H_
#define TRANSACTION_H_
#include <string>
using namespace std;

class Transaction {
	friend ostream& operator<<(ostream& out, const Transaction& trans);
public:
	Transaction();
	Transaction(char type, int accountID);
	Transaction(char type, int accountID, int fundID);
	Transaction(char type, string last, string first, int accountID);
	Transaction(char type, int accountID, int fundID, int amount);
	Transaction(char type, int accountID, int fundID, int amount, int transferID, int transferFundID);

	Transaction(char type, int accountID, int fundID, string success, int amount);
	Transaction(char type, int accountID, int fundID, int amount, int transferID, int transferFundID, string success);

	char getType() const;
	string getLast() const;
	string getFirst() const;
	int getAccountID() const;
	int getFundID() const;
	int getTransferAccountID() const;
	int getTransferFundID() const;
	int getAmount() const;

	bool Success();


private:
	char type_;
	string first_;
	string last_;
	string success_;
	int accountID_;
	int fundID_;
	int transferID_;
	int transferFundID_;
	int amount_;
};
#endif