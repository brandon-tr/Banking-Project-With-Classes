#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <list>
#include <ctime>
#include <chrono>
#include <tuple>

const int totalCapacity = 1000;

using namespace std;

tuple<int, int, int>current_datetime()
{
	auto start = chrono::system_clock::now();
	struct tm t;
	time_t now = time(0);
	localtime_s(&t, &now);
	int month = 1 + t.tm_mon;
	int year = 1900 + t.tm_year;
	int day = t.tm_mday;
	return make_tuple(day, month, year);
}

struct date
{
	int day;
	int month;
	int year;
};

class Person
{
public:
	Person()
	{
		this->fname = "No Name \n";
		this->lname = "No Name \n";
		this->ssn = 111111111;;
		this->birthDate.day = 01;
		this->birthDate.month = 01;
		this->birthDate.year = 01;
	}
	Person(string fname, string lname, date birthDate, int ssn)
	{
		this->birthDate = birthDate;
		this->fname = fname;
		this->lname = lname;
		this->ssn = ssn;
	};
	void print()
	{
		cout << this->fname << " " << this->lname << " " << this->birthDate.day << "/" << this->birthDate.month << "/" << this->birthDate.year << " " << this->ssn << endl;
	}
	//Getters
	string getFname()
	{
		return this->fname;
	}
	string getLname()
	{
		return this->lname;
	}
	int returnSsn()
	{
		return this->ssn;
	}
	date returnBirthDate()
	{
		return this->birthDate;
	}
	//Setters
	void setPersonInfo(string fName, string lName, date birthDate, int ssn)
	{
		this->fname = fName;
		this->lname = lName;
		this->birthDate = birthDate;
		this->ssn = ssn;
	}
private:
	string fname;
	string lname;
	int ssn;
	date birthDate;
};

class Account
{
	friend int closeAccount();
private:
	Person owner;
	int acctNo;
	double balance;
	date openDate;
	date closeDate;
	bool closed;
public:
	Account()
	{
		this->acctNo = 0;
		this->balance = 0;
		this->openDate.day = 01;
		this->openDate.month = 01;
		this->openDate.year = 01;
		this->closeDate.month = 01;
		this->closeDate.day = 01;
		this->closeDate.year = 01;
		this->closed = false;
	};
	Account(string fname, string lname, int day, int month, int year, double balance, int acctNo, date openDate, date closeDate)
	{
		this->acctNo = acctNo;
		this->balance = balance;
		this->openDate.day = day;
		this->openDate.year = year;
		this->openDate.month = month;
		this->closeDate.day = day;
		this->closeDate.month = month;
		this->closeDate.year = year;
	};
	void printAccount()
	{
		owner.print();
		cout << " " << this->acctNo << " " << this->balance << " " << this->openDate.day << "/" << this->openDate.month << "/" << this->openDate.year << endl;
	};
	void depositMoney(double amount, int numOfAccounts, Account account[], int index)
	{
		account[index].balance += amount;
		ofstream outFile;
		ifstream inFile;
		string line;
		list<string> oldFileList;
		string fileName = to_string(account[index].acctNo);
		int month, day, year;
		tie(month, day, year) = current_datetime();
		string date = to_string(month) + "/" + to_string(day) + "/" + to_string(year);
		inFile.open(fileName + ".txt");
		while (getline(inFile, line))
		{
			if (line.length() > 0)
			{
				oldFileList.emplace_back(line);
			}
		}
		inFile.close();
		outFile.open(fileName + ".txt");
		if (oldFileList.size() > 0)
		{
			for (auto const& i : oldFileList)
			{
				outFile << i;
				outFile << "\n";
			}
		}
		outFile << "You deposited " << amount << "      " << date;
		outFile.close();

		outFile.open("accounts.txt");
		for (int i = 0; i < numOfAccounts; i++)
		{
			outFile << account[i].returnPersonFname() << " " << account[i].returnPersonLname() << " " << account[i].returnBirthDate().day << " "
				<< account[i].returnBirthDate().month << " " << account[i].returnBirthDate().year << " " << account[i].returnBalance() << " "
				<< account[i].returnAcctNo() << " " << account[i].returnPersonSsn() << " " << account[i].returnClosed() << "\n";
		}
		outFile.close();
	}
	void withdrawMoney(double amount, int numOfAccounts, Account account[], int index)
	{
		account[index].balance -= amount;
		ofstream outFile;
		ifstream inFile;
		string line;
		list<string> oldFileList;
		string fileName = to_string(account[index].acctNo);
		int month, day, year;
		tie(month, day, year) = current_datetime();
		string date = to_string(month) + "/" + to_string(day) + "/" + to_string(year);
		inFile.open(fileName + ".txt");
		while (getline(inFile, line))
		{
			if (line.length() > 0)
			{
				oldFileList.emplace_back(line);
			}
		}
		inFile.close();
		outFile.open(fileName + ".txt");
		if (oldFileList.size() > 0)
		{
			for (auto const& i : oldFileList)
			{
				outFile << i;
				outFile << "\n";
			}
		}
		outFile << "You withdrew " << amount << "      " << date;
		outFile.close();

		outFile.open("accounts.txt");
		for (int i = 0; i < numOfAccounts; i++)
		{
			outFile << account[i].returnPersonFname() << " " << account[i].returnPersonLname() << " " << account[i].returnBirthDate().day << " "
				<< account[i].returnBirthDate().month << " " << account[i].returnBirthDate().year << " " << account[i].returnBalance() << " "
				<< account[i].returnAcctNo() << " " << account[i].returnPersonSsn() << " " << account[i].returnClosed() << "\n";
		}
		outFile.close();
	}
	void transferMoney(double amount, Account account[], int idxFirstAccount, int idxSecondAccount, int numOfAccounts)
	{
		if (account[idxFirstAccount].balance >= amount)
		{
			withdrawMoney(amount, numOfAccounts, account, idxFirstAccount);
			depositMoney(amount, numOfAccounts, account, idxSecondAccount);
		}
		else
		{
			cout << "Error not enough money" << endl;
		}
	}
	//Getters
	string returnPersonFname()
	{
		return this->owner.getFname();
	}
	string returnPersonLname()
	{
		return this->owner.getLname();
	}
	int returnPersonSsn()
	{
		return this->owner.returnSsn();
	}
	date returnBirthDate()
	{
		return this->owner.returnBirthDate();
	}
	int returnAcctNo()
	{
		return this->acctNo;
	}
	double returnBalance()
	{
		return this->balance;
	}
	date returnOpenDate()
	{
		return this->openDate;
	}
	date returnCloseDate()
	{
		return this->closeDate;
	}
	bool returnClosed()
	{
		return this->closed;
	}
	//Setters
	void setAccountInfo(string fName, string lName, int acctNo, double balance, date openDate, int socialSecurity, bool closed)
	{
		this->acctNo = acctNo;
		this->balance = balance;
		this->openDate = openDate;
		this->closed = closed;
		this->owner.setPersonInfo(fName, lName, openDate, socialSecurity);
	}
	void setAccountForClosing(bool closing)
	{
		this->closed = closing;
	}
	void setCloseDate(date closed)
	{
		this->closeDate = closed;
	}

};


int openAccount(Account account[totalCapacity], int numOfAccounts)
{
	ofstream outFile;
	ifstream inFile;
	string line;

	string fname, lname;
	date birthdate, openDate;
	int acctNo, socialSecurity;
	double balance = 0;
	bool flag = false;
	list<string> oldAccountList;

	cin >> fname >> lname >> birthdate.day >> birthdate.month >> birthdate.year >> balance >> acctNo >> socialSecurity;
	string fileName = to_string(acctNo);
	inFile.open("accounts.txt");
	while (getline(inFile, line))
	{
		oldAccountList.emplace_back(line);
	}
	inFile.close();
	for (int i = 0; i <= numOfAccounts; i++)
	{
		if (i == numOfAccounts)
		{
			account[i].setAccountInfo(fname, lname, acctNo, balance, birthdate, socialSecurity, flag);
			account[i].printAccount();
			numOfAccounts++;
			break;
		}
	}
	outFile.open("accounts.txt");
	for (auto const& i : oldAccountList)
	{
		outFile << i << "\n";
	}
	outFile << fname << " " << lname << " " << birthdate.day << " " << birthdate.month << " " << birthdate.year << " " << balance << " " << acctNo << " " << socialSecurity << " " << 0;
	outFile.close();

	outFile.open(fileName + ".txt");
	outFile << "You opened a new account with the balance of  " << balance;
	outFile.close();
	return numOfAccounts;
}

void closeAccount(Account account[], int index, int numOfAccounts)
{
	ofstream outFile;
	int month, day, year;
	tie(day, month, year) = current_datetime();
	date dateClosed;
	dateClosed.day = day;
	dateClosed.month = month;
	dateClosed.year = year;

	//Changing  Account Info
	account[index].setCloseDate(dateClosed);
	account[index].setAccountForClosing(true);
	//End

	outFile.open("accounts.txt");

	//Loop through account array and edit the accounts.txt file
	for (int i = 0; i < numOfAccounts; i++)
	{
		outFile << account[i].returnPersonFname() << " " << account[i].returnPersonLname() << " " << account[i].returnBirthDate().day << " "
			<< account[i].returnBirthDate().month << " " << account[i].returnBirthDate().year << " " << account[i].returnBalance() << " "
			<< account[i].returnAcctNo() << " " << account[i].returnPersonSsn() << " " << account[i].returnClosed() << "\n";
	}
	//end
	outFile.close();
	ifstream inFile;
	string fileName = to_string(account[index].returnAcctNo());
	inFile.open(fileName + ".txt");
	if (inFile.fail())
	{
		outFile.open(fileName + ".txt");
		outFile << "You closed account number  " << account[index].returnAcctNo() << "on " << dateClosed.day << "/" << dateClosed.month << "/" << dateClosed.year << "\n";
		outFile.close();
	}
	else
	{
		list<string> oldAccountList;
		string line;
		while (getline(inFile, line))
		{
			oldAccountList.emplace_back(line);
		}
		inFile.close();
		outFile.open(fileName + ".txt");
		for (auto i : oldAccountList)
		{
			outFile << i << "\n";
		}
		outFile << "You closed account number  " << account[index].returnAcctNo() << " on " << dateClosed.day << "/" << dateClosed.month << "/" << dateClosed.year << "\n";
		outFile.close();
	}

}

int SearchForAccountIndexUsingAcctOwnersName(Account account[], int numOfAccounts)
{
	string inputFname, inputLname;
	cin >> inputFname >> inputLname;
	for (int i = 0; i < numOfAccounts; i++)
	{
		if (account[i].returnPersonFname() == inputFname && account[i].returnPersonLname() == inputLname)
		{
			cout << "Found him" << endl;
			return i;
		}
	}
	return -1;
}
int SearchForAccountIndexUsingAcctNumber(Account account[], int numOfAccounts)
{
	int acctNo;
	cin >> acctNo;
	for (int i = 0; i < numOfAccounts; i++)
	{
		if (account[i].returnAcctNo() == acctNo)
		{
			cout << "Found him" << endl;
			return i;
		}
	}
	return -1;
}
void sortBalances(Account account[], int numOfAccounts)
{
	list<Account> listOfAccounts;
	for (int i = 0; i < numOfAccounts; i++)
	{
		listOfAccounts.emplace_back(account[i]);
	}
	listOfAccounts.sort([](Account & a, Account & b) { return a.returnBalance() > b.returnBalance(); });

	for (auto i : listOfAccounts)
	{
		i.printAccount();
	}
}
void sortNames(Account account[], int numOfAccounts)
{
	list<Account> listOfAccounts;
	for (int i = 0; i < numOfAccounts; i++)
	{
		listOfAccounts.emplace_back(account[i]);
	}
	listOfAccounts.sort([](Account & a, Account & b) { return a.returnPersonLname() < b.returnPersonLname(); });

	for (auto i : listOfAccounts)
	{
		i.printAccount();
	}
}

int main()
{
	int numOfAccounts = 0;
	ifstream inFile;
	inFile.open("accounts.txt");
	string line;
	Account account[totalCapacity];


	if (inFile.fail())
	{
		cout << "Failed to open file" << endl;
	}
	else
	{
		int i = 0;
		string fname, lname;
		date birthdate;
		int acctNo, socialSecurity;
		double balance;
		int flag;
		while (inFile >> fname >> lname >> birthdate.day >> birthdate.month >> birthdate.year >> balance >> acctNo >> socialSecurity >> flag)
		{
			account[i].setAccountInfo(fname, lname, acctNo, balance, birthdate, socialSecurity, flag);
			i++;
		}
		numOfAccounts = i;
	}
	//openAccount(account, numOfAccounts);
	//closeAccount(account, 2, numOfAccounts);
	//SearchForAccountIndexUsingAcctOwnersName(account, numOfAccounts);
	//SearchForAccountIndexUsingAcctNumber(account, numOfAccounts);
	//sortBalances(account, numOfAccounts);
	//sortNames(account, numOfAccounts);
	//account->transferMoney(.05, account, 2, 0, numOfAccounts);
}
