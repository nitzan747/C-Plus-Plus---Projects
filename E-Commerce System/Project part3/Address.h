#ifndef Address_H
#define Address_H
#pragma warning(disable : 4996)
#include "Definitions.h"
#include <ostream>
#include <stdio.h>
#include <string.h>
#include<string>
#include <iostream>
using namespace std;

class Address
{
private:
	std::string country;
	std::string city;
	std::string street;
	int houseNumber;
public:
	Address(const string& country, const string& city, const string& street, int houseNumber); //constructor
	Address(const Address& other); //copy c'tor
	Address(Address&& other); //move c'tor
	
	bool setCountry(const string& country);
	bool setCity(const string& city);
	bool setStreet(const string& street);
	bool setHouseNumber(const int& houseNumber);

	const string& getCountry() const;
	const string& getCity() const;
	const string& getStreet() const;
	int getHouseNumber()const;


	friend ostream& operator<<(ostream& out, const Address& address)
	{
		if (typeid(out) == typeid(ofstream))
			out << address.country << " " << address.city << " " << address.street << " " << address.houseNumber;
		else
			out << "Country: " << address.country << "\nCity: " << address.city << "\nStreet: " << address.street << "\nHouse number: " << address.houseNumber << endl;
		return out;
	}
	
	friend  istream& operator>>(istream& in, Address& address)
	{
		std::string country, city, street;
		in >> country >> city >> street >> address.houseNumber;
		address.setCountry(country);
		address.setCity(city);
		address.setStreet(street);
		return in;			
	}
};

#endif // !Address_H