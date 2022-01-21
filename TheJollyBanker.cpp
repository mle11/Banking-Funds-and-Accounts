#include "Bank.h"


int main(int argc, char* argv[])
{
	Bank bank;
	bank.ReadTransactions(argv[1]);
	bank.Process();
	bank.Display(); 
}