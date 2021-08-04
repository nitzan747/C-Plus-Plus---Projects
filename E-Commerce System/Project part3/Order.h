#ifndef Order_H
#define Order_H
#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
#include "Array.h"
#include "Definitions.h"
#include "product.h"

class Order
{
private:
	std::string buyerName;
	double totalSumCost;
	Array<Product> productsArray;

public:
	Order(const string& buyerName, double totalSumCost = 0); //constructor
	Order(const Order& other); //copy c'tor

	void setBuyerName(const string& buyerName);
	void setTotalSumCost(double totalSumCost);
	void setProductsArray(Array<Product> productsArray);

	const string& getBuyerName() const;
	double getTotalSumCost() const;
	Array<Product> getProductsArray() const;

	void addProduct(const Product& product);
	void updateTotalSumCost();
};

#endif // !Order_H