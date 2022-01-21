#include "Bank.h"
#include "Transaction.h"
#include "Account.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>


Bank::Bank() {
}

bool Bank::ReadTransactions(string fileName) {
	ifstream in(fileName);
	string readLine;
	if (!in) {
		cout << "Cannot Open!" << endl;
	}
	while (!in.eof()) {
		getline(in, readLine);
		if (readLine.empty()) {
			break;
		}
		istringstream parseline(readLine);
		char type;
		parseline >> type;

		if (type == 'O') {
			string first;
			string last;
			int accountID;
			parseline >> accountID >> last >> first;
			Transaction add(type, first, last, accountID);
			transactionList.push(add);
		} else if (type == 'W' || type == 'D') {
			int accountID;
			int fundID;
			int amount;
			parseline >> accountID >> fundID >> amount;
			Transaction add(type, accountID, fundID, amount);
			transactionList.push(add);
		}
		else if (type == 'T') {
			int accountID;
			int fundID;
			int trasnferAccountID;
			int transferFundID;
			int amount;
			parseline >> accountID >> fundID >> trasnferAccountID >> transferFundID >> amount;
			Transaction add(type, accountID, fundID, amount, trasnferAccountID, transferFundID);
			transactionList.push(add);
		} else if (type == 'A' || type == 'a') {
			int accountID;
			parseline >> accountID;
			Transaction add(type, accountID);
			transactionList.push(add);
		} else if (type == 'F') {
			int accountID, fundID;
			parseline >> accountID >> fundID;
			Transaction add(type, accountID, fundID);
			transactionList.push(add);
		} else {
			cout << "ERROR" << endl;
		}
	}
	return false;
}

void Bank::Process() {
	while (!transactionList.empty()) {
		Transaction transaction = transactionList.front();
		if (transaction.getType() == 'O' || transaction.getType() == 'o') {
			Account* account = new Account(transaction.getLast(), transaction.getFirst(), transaction.getAccountID());
			accountList.Insert(account);
		} else if (transaction.getType() == 'D' || transaction.getType() == 'd') {
			int accountID = transaction.getAccountID();
			int fundID = transaction.getFundID();
			int amount = transaction.getAmount();
			Account* account;
			if (accountList.Retrieve(accountID, account)) {
				account->AddFunds(fundID, amount);
				account->Record(transaction, fundID);
			}

		} else if (transaction.getType() == 'W' || transaction.getType() == 'w') {
			int accountID = transaction.getAccountID();
			int fundID = transaction.getFundID();
			int amount = transaction.getAmount();
			Account* account;
			if (accountList.Retrieve(accountID, account))
			{
				account->RemoveJointFunds(fundID, amount, transaction);
			}

		} else if (transaction.getType() == 'T' || transaction.getType() == 't') {
			Account* firstAccount;
			Account* secondAccount;
			int accountID = transaction.getAccountID();
			int transferAcctNum = transaction.getTransferAccountID();
			int fundID = transaction.getFundID();
			int transferFundID = transaction.getTransferFundID();
			int amount = transaction.getAmount();
			if (accountList.Retrieve(accountID, firstAccount) && accountList.Retrieve(transferAcctNum, secondAccount)) {
				if (firstAccount->RemoveJointFunds(fundID, amount, transaction)) {
					secondAccount->AddFunds(transferFundID, amount);
					secondAccount->Record(transaction, transferFundID);
				} else {
					cerr << "ERROR: Not Enought Funds to Transer  " << amount << " " << "from " << secondAccount->getAccountID() << fundID << " to " << firstAccount->getAccountID() << transferFundID << endl;
					Transaction addTransactions('T', accountID, fundID, amount, transferAcctNum, transferFundID, "(Failed)");
					secondAccount->Record(addTransactions, transferFundID);
				}
			}

		} else if (transaction.getType() == 'F' || transaction.getType() == 'f') {
			Account* account;
			int fundID = transaction.getFundID();
			int accountID = transaction.getAccountID();
			if (accountList.Retrieve(accountID, account)) {
				account->PrintFundHistory(fundID);
				cout << endl;
			}
		} else if (transaction.getType() == 'A' || transaction.getType() == 'a') {
			Account* account;
			int accountID = transaction.getAccountID();
			if (accountList.Retrieve(accountID, account)) {
				account->PrintHistory();
				cout << endl;
			}
		}
		transactionList.pop();
	}
}

void Bank::Display() {
	cout << "FINAL BALANCES:" << endl;
	accountList.Display();
}