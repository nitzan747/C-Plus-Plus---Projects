#include "Order.h"

Order::Order(const string& buyerName, double totalSumCost) //constructor
{
	if (!buyerName.empty())
		this->buyerName = buyerName;
	this->totalSumCost = totalSumCost;
	this->productsArray = Array<Product>();
}

Order::Order(const Order& other)//copy c'tor
{
	this->totalSumCost = other.getTotalSumCost();
	this->productsArray = other.productsArray;
}


void Order::setBuyerName(const string& buyerName)
{
	this->buyerName = buyerName;
}


void Order::setTotalSumCost(double totalSumCost)
{
	this->totalSumCost = totalSumCost;
}

void Order::setProductsArray(Array <Product> productsArray)
{
	this->productsArray = productsArray;
}


const string& Order::getBuyerName() const
{
	return buyerName;
}

double Order::getTotalSumCost() const
{
	return totalSumCost;
}

Array<Product> Order::getProductsArray() const
{
	return productsArray;
}


void Order::addProduct(const Product& product)//Add product to order
{
	productsArray += product;
}


void Order::updateTotalSumCost()//Calculate the cost of order
{
	double sumCost = 0;
	int i, logicProductsArraySize = productsArray.getLogSize();
	for (i = 0; i < logicProductsArraySize; i++)
		sumCost += productsArray.getArrByIndex(i).getPrice();
	
	this->totalSumCost = sumCost;
}