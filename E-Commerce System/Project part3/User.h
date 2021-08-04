#ifndef User_H
#define User_H
#pragma warning(disable : 4996)

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

#include "Address.h"
#include "Definitions.h"

class User
{
private:
	std::string userName;
	std::string password;
	Address* address;// by pointer

public:
	User(const string& userName, const string& password, Address* address);//constructor
	User(const User& Other);//copy c'tor
	User(User&& Other);//move c'tor
	virtual ~User();

	bool setUserName(const string& name);
	bool setPassword(const string& password);
	void setAddress(Address& address);

	const string& getUserName() const;
	const string& getPassword() const;
	Address* getAddress() const;



	friend ostream& operator<< (ostream& out, const User& user)
	{
		if (typeid(out) == typeid(ofstream))
			out << user.userName << " " << user.password << " " << *(user.address);
		else
			out << "User name: " << user.userName << "\n Password: " << user.password << "\n Address: " << *(user.address) << endl;
		return out;
	}
	
	friend istream& operator>> (istream& in, User& user)
	{
		std::string userName, password;
		if (typeid(in) == typeid(ifstream))
		{
			in >> userName >> password >> *(user.address);
			user.setUserName(userName);
			user.setPassword(password);
		}
		else//typeid(in)==typeid(ostream)
		{
			char delimiter;
			in >> user.userName >> user.password >> delimiter>> *(user.address);
		}
		return in;
	}	
};

#endif // !User_H
