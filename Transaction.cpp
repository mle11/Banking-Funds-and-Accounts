#include <iostream>
#include "Transaction.h"


Transaction::Transaction() {

}

Transaction::Transaction(char type, int accountID) {
	type_ = type;
	accountID_ = accountID;
}

Transaction::Transaction(char type, int accountID, int fundID) {
	type_ = type;
	accountID_ = accountID;
	fundID_ = fundID;
}

Transaction::Transaction(char type, string last, string first, int accountID) {
	type_ = type;
	last_ = last;
	first_ = first;
	accountID_ = accountID;
}

Transaction::Transaction(char type, int accountID, int fundID, int amount) {
	type_ = type;
	accountID_ = accountID;
	fundID_ = fundID;
	amount_ = amount;
}

Transaction::Transaction(char type, int accountID, int fundID, int amount, int transferID, int transferFundID) {
	type_ = type;
	accountID_ = accountID;
	fundID_ = fundID;
	transferID_ = transferID;
	transferFundID_ = transferFundID;
	amount_ = amount;
}

Transaction::Transaction(char type, int accountID, int fundID, string success, int amount) {
	type_ = type;
	accountID_ = accountID;
	fundID_ = fundID;
	amount_ = amount;
	success_ = success;
}

Transaction::Transaction(char type, int accountID, int fundID, int amount, int transferID, int transferFundID, string success) {
	type_ = type;
	accountID_ = accountID;
	fundID_ = fundID;
	transferID_ = transferID;
	transferFundID_ = transferFundID;
	amount_ = amount;
	success_ = success;
}

//Checks if the string fail is empty, if it is not empty the transaction failed to process
bool Transaction::Success() {
	return success_.empty();
}

char Transaction::getType() const {
	return type_;
}

string Transaction::getLast() const {
	return last_;
}

string Transaction::getFirst() const {
	return first_;
}

int Transaction::getAccountID() const {
	return accountID_;
}

int Transaction::getAmount() const {
	return amount_;
}

int Transaction::getFundID() const {
	return fundID_;
}

int Transaction::getTransferAccountID() const {
	return transferID_;
}

int Transaction::getTransferFundID() const {
	return transferFundID_;
}

//This overloaded operater check to see if the string fail is empty, if it is empty
//there is a "failed" string attached to the end of the output
ostream& operator<<(ostream& stream, const Transaction& trans) {
	if (trans.success_.empty()) {
		if (trans.getType() == 'D' || trans.getType() == 'd' || trans.getType() == 'W'
			|| trans.getType() == 'w') {
			stream << " " << trans.getType() << " " << trans.getAccountID() << " " << 
				trans.getFundID() << " " << trans.getAmount();
		} else if (trans.getType() == 'T' || trans.getType() == 't') {
			stream << " " << trans.getType() << " " << trans.getAccountID() << " " <<
				trans.getFundID() << " " << trans.getTransferAccountID() << " " << 
				trans.getTransferFundID() << " " << trans.getAmount();
		} else {
		}
	} else {
		if (trans.getType() == 'D' || trans.getType() == 'd' || trans.getType() == 'W'
			|| trans.getType() == 'w') {
			stream << " " << trans.getType() << " " << trans.getAccountID() << " " <<
				trans.getFundID() << " " << trans.getAmount() << " (Failed)";
		} else if (trans.getType() == 'T' || trans.getType() == 't') {
			stream << " " << trans.getType() << " " << trans.getAccountID() << " " <<
				trans.getFundID() << " " << trans.getTransferAccountID() << " " << 
				trans.getTransferFundID() << " " << trans.getAmount() << " " << 
				"(Failed)";
		} else {
		}

	}
	return stream << endl;

}