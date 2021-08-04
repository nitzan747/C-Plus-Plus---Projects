#ifndef Product_H
#define Product_H
#pragma warning(disable : 4996)

#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

#include "Definitions.h"

class Seller;

class Product
{
public:
	enum eCategory { Children, Electricity, Clothing, Office };

private:
	std::string name;
	eCategory category;
	double price;
	int serial_number;
	Seller* seller;
	static int counter;

public:
	Product(const string& name, eCategory category , double& price, Seller*& seller); //constructor
	Product(const Product& other);//copy c'tor 
	~Product(); //destructor

	void setName(const string& n);
	void setCategory(eCategory c);
	void setPrice(const double& p);
	bool setSeller(Seller* Seller);

	const string& getName()const;
	eCategory getCategory()const;
	double getPrice()const;
	int getSerialNumber()const;
	Seller* getSeller() const;

	const Product& operator=(const Product& other);
};

#endif // !Product_H