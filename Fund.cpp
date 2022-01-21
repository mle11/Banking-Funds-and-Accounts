#include "Fund.h"


Fund::Fund() {
	balance_ = 0;
}

bool Fund::Add(int amount) {
	balance_ += amount;
	return true;
}

bool Fund::Subtract(int amount) {
	balance_ -= amount;
	return true;
}

bool Fund::Balance(int amount) {
	return balance_ >= amount;
}


bool Fund::Record(Transaction trans) {
	history_.push_back(trans);
	return true;
}

void Fund::PrintHistory() {
	if (history_.size() == 0) {
		return;
	} else {
		cout << fund_ << ": $" << balance_ << endl;
		for (int i = 0; i < history_.size(); i++) {
			cout << " " << history_[i];
		}
	}
}

void Fund::PrintFundHistory() {
	for (int i = 0; i < history_.size(); i++) {
		cout << " " << history_[i];
	}
}

void Fund::setName(string name) {
	fund_ = name;
}

int Fund::getBalance() const {
	return balance_;
}

string Fund::getName() const {
	return fund_;
}
