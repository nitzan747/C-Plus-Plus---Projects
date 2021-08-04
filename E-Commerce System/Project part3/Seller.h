#ifndef Seller_H
#define Seller_H
#pragma warning(disable : 4996)

#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

#include "FeedBack.h"
#include "Definitions.h"
#include "User.h"

class Seller:virtual public User
{
private:	
	vector<FeedBack*> feedbackArray;
	vector<Product*> listOfProducts;

public:
	Seller(const string& userName, const string& password, Address* address);//constructor
	Seller(const Seller& other);//copy ctor 
	Seller(Seller&& other);//move c'tor
	~Seller();//destructor

	vector<FeedBack*> getFeedbackArray();
	vector<Product*> getListOfProducts();

	void AddToProductList(Product* newProduct);
	void addFeedbackToSeller(FeedBack* feedback);
};

#endif // !Seller_H