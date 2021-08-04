#include "Address.h"

static bool isStrCorrect(const string& str);
static bool isLetter(const char& c);

Address::Address(const string& country, const string& city, const string& street, int houseNumber) // constructor
{
	Address::setCountry(country);
	Address::setCity(city);
	Address::setStreet(street);
	Address::setHouseNumber(houseNumber);
}

Address::Address(const Address& other) //copy c'tor
{
	this->country = other.getCountry();
	this->city = other.getCity();
	this->street = other.getStreet();
	this->houseNumber = other.getHouseNumber();
}

Address::Address(Address&& other) //move ctor
{
	this->country = other.getCountry();
	this->city = other.getCity();
	this->street = other.getStreet();
	this->houseNumber = other.getHouseNumber();
}


bool Address::setCountry(const string& country)
{
	if (!isStrCorrect(country)) // The country name is illegal
		return false;
	this->country = country;
	return true;
}

bool Address::setCity(const string& city)
{
	if (!isStrCorrect(city)) // The city name is illegal	
		return false;
	this->city = city;
	return true;
}

bool Address::setStreet(const string& street)
{
	if (!isStrCorrect(street)) // The street name is illegal	
		return false;
	this->street = street;
	return true;
}

bool Address::setHouseNumber(const int& houseNumber)
{
	if (houseNumber <= 0) // The house number is illegal
		return false;
	this->houseNumber = houseNumber;
	return true;
}

const string& Address::getCountry() const
{
	return country;
}

const string& Address::getCity() const
{
	return city;
}

const string& Address::getStreet() const
{
	return street;
}

int Address::getHouseNumber() const
{
	return houseNumber;
}


static bool isStrCorrect(const string& str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (!isLetter(str[i]))
			return false;
		i++;
	}
	return true;
}

static bool isLetter(const char& c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a') && (c <= 'z')) // c is capital letter or small letter
		return true;
	return false;
}