#include "User.h"

static bool checkLettersAndNumbersOnly(const string& str);
static bool userNameAboveMinSize(const string& name);
static bool passwordInCorrectLength(const string& pass);

User::User(const string& userName, const string& password, Address* address)//constructor
{
	this->userName = userName;
	this->password = password;
	this->address = new Address(*address);
}

User::User(const User& other)//copy c'tor
{
	this->userName = other.userName;//copying Other username
	this->password = other.password;//copying Other password
	this->address = new Address(*other.address);//copy c'tor 
}

User::User(User&& other)//move c'tor
{
	this->userName = other.userName;
	other.setUserName(NULL);
	this->password = other.password;
	other.setPassword(NULL);

	this->address = other.address;//will point to other.address -by pointer 
	other.address = NULL;
}

User::~User()//destructor
{
	delete address;
}


bool User::setUserName(const string& name)
{
	if (checkLettersAndNumbersOnly(name) && userNameAboveMinSize(name)) //checks that the name is right by the rules
	{
		this->userName = name;
		return true;
	}
	return false; //Didnt pass the check (and the dinamic string (TempPassWord) will be released)
}

bool User::setPassword(const string& password)
{
	if (checkLettersAndNumbersOnly(password) && passwordInCorrectLength(password)) //checks that the password is right by the rules
	{
		this->password = password;
		return true;
	}
	return false; //Didnt pass the check (and the dinamic string (TempPassWord) will be released afterwards)
}

void User::setAddress(Address& address)
{
	this->address = new Address(address);//will point to the new address
}

const string& User::getUserName() const
{
	return userName;
}

const string& User::getPassword() const
{
	return password;
}

Address* User::getAddress() const
{
	return address;
}


static bool checkLettersAndNumbersOnly(const string& str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] < 48) || (str[i] > 57 && str[i] < 65) || (str[i] > 90 && str[i] < 97) || (str[i] > 122))//checking if there is any char that dosent contain a digit or letter 
			return false;
	}
	return true;
}

static bool userNameAboveMinSize(const string& name)//Check if user name is not longer than 20 letters
{
	int size = name.length();
	if (size >= 6)
		return true;
	return false;
}

static bool passwordInCorrectLength(const string& pass)//Check if password has exactly 8 characters
{
	int size = pass.length();
	if (size == PASSWORD_LENGTH-1)
		return true;
	return false;
}