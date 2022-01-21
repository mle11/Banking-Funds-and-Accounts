#include "Account.h"

Account::Account() {

}

Account::Account(string first, string last, int accountID) {
	first_ = first;
	last_ = last;
	accountID_ = accountID;
	string fundNames[] = { "Money Market", "Prime Money Market","Long-Term Bond", 
		"Short-Term Bond","500 Index Fund", "Capital Value Fund",
		"Growth Equity Fund", "Growth Index Fund"};
	for (int i = 0; i < 8; i < i++) {
		funds[i].setName(fundNames[i]);
	}
}

int Account::getAccountID() const {
	return accountID_;
}

int Account::getBalance(int fundID) const {
	return funds[fundID].getBalance();
}

string Account::getFundName(int fundID) {
	return funds[fundID].getName();
}

string Account::getFirst() const {
	return first_;
}

string Account::getLast() const {
	return last_;
}

void Account::setFundID(int fundID) {
	fundID_ = fundID;
}

void Account::AddFunds(int fundID, int amount) {
	funds[fundID].Add(amount);
}

void Account::RemoveFunds(int firstFund, int secondFund, int amount) {
	if (((funds[firstFund].getBalance() + funds[secondFund].getBalance()) 
		>= amount)) {
		int balance = funds[firstFund].getBalance();
		funds[firstFund].Subtract(balance);
		Transaction addToHistory('W', getAccountID(), firstFund, balance);
		funds[firstFund].Record(addToHistory);
		amount = amount - balance;
		funds[secondFund].Subtract(amount);
		Transaction addToHistory2('W', getAccountID(), secondFund, amount);
		funds[secondFund].Record(addToHistory2);
	} else {
		int balance = funds[firstFund].getBalance();
		if (balance > amount) {
			funds[firstFund].Subtract(balance);
			Transaction addToHistory('W', getAccountID(), firstFund, balance);
			funds[firstFund].Record(addToHistory);
			amount = amount - balance;
		}
		if (funds[secondFund].Balance(amount)) {
			funds[secondFund].Subtract(amount);
			Transaction addToHistory('W', getAccountID(), secondFund, amount);
			funds[secondFund].Record(addToHistory);
		} else {
			cerr << "Error: Not Enought Funds to withdraw " << amount << " " << 
				"from " << getLast() << " " << getFirst() << " " << 
				getFundName(secondFund) << endl;
			Transaction addToHistory('W', getAccountID(), secondFund, "Failed",
				amount);
			funds[secondFund].Record(addToHistory);
		}
	}
}

bool Account::RemoveJointFunds(int fundID, int amount, Transaction frontTrans) {
	if (fundID == 0 || fundID == 1 || fundID == 2 || fundID == 3) {
		if (fundID == 0 || fundID == 1) {
			if (funds[fundID].Balance(amount)) {
				funds[fundID].Subtract(amount);
				funds[fundID].Record(frontTrans);
				return true;
			} else if (((funds[0].getBalance() + funds[1].getBalance())
				>= amount)) {
				if (fundID == 0) {
					RemoveFunds(0, 1, amount);
				} else {
					RemoveFunds(1, 0, amount);
				}
			} else {
				Error(amount, getLast(), getFirst(), fundID);
				if (fundID == 0) {
					RemoveFunds(0, 1, amount);
				} else {
					RemoveFunds(1, 0, amount);
				}
				return false;
			}
		} else if (fundID == 2 || fundID == 3) {
			if (funds[fundID].Balance(amount)) {
				funds[fundID].Subtract(amount);
				funds[fundID].Record(frontTrans);
				return true;
			} else if (((funds[2].getBalance() + funds[3].getBalance())
				>= amount)) {
				if (fundID == 2) {
					RemoveFunds(2, 3, amount);
				} else {
					RemoveFunds(3, 2, amount);
				}
			} else {
				Error(amount, getLast(), getFirst(), fundID);
				if (fundID == 2) {
					RemoveFunds(2, 3, amount);
				} else {
					RemoveFunds(3, 2, amount);
				}
				return false;
			}
		}
	} else {
		if (funds[fundID].Balance(amount)) {
			funds[fundID].Subtract(amount);
			funds[fundID].Record(frontTrans);
			return true;
		} else {
			Error(amount, getLast(), getFirst(), fundID);
			return false;
		}
	}
	return true;
}

void Account::Error(int amount, string last_, string first_, int fundID){
	cerr << "ERROR: Not enough funds to withdraw " << amount << " " << "from "
		<< first_ << " " << last_ << " " << getFundName(fundID) << endl;
	Transaction addToHistory('W', getAccountID(), fundID, "Failed", amount);
	funds[fundID].Record(addToHistory);
}

void Account::Record(Transaction trans, int fundID) {
	funds[fundID].Record(trans);
}

void Account::PrintHistory() {
	cout << "Transaction History for " << first_ << " " << last_ << " " <<
		"by fund." << endl;
	for (int i = 0; i < 8; i++) {
		funds[i].PrintHistory();
	}
}

void Account::PrintFundHistory(int fundID) {
	cout << "Transaction History for " << first_ << " " << last_ << " " << 
		getFundName(fundID) << ": $" << getBalance(fundID) << endl;
	funds[fundID].PrintFundHistory();
}

ostream& operator<<(ostream& stream, Account& account) {
	stream << account.getFirst() << " " << account.getLast() << 
		" Account ID: " << account.getAccountID() << endl;
	for (int i = 0; i < 8; i++) {
		stream << "    " << account.getFundName(i) << ": $" << 
			account.getBalance(i);
		stream << endl;
	}

	return stream;

}