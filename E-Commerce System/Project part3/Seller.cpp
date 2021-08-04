#include "Seller.h"

Seller::Seller(const string& userName, const string& password, Address* address) : User(userName, password, address)//constructor
{
	
}

Seller::Seller(const Seller& other) : User(other)//copy ctor
{
	this->feedbackArray = other.feedbackArray;// c'tor of feedBack
	this->listOfProducts = other.listOfProducts;
}

Seller::Seller(Seller&& other) : User(other)//move c'tor
{
	feedbackArray = other.feedbackArray;
	listOfProducts = other.listOfProducts;
}

Seller:: ~Seller()//destructor
{
	vector<FeedBack*>::iterator itr = feedbackArray.begin();
	vector<FeedBack*>::iterator itrEnd = feedbackArray.end();
	for (; itr != itrEnd; ++itr)
		delete *itr;
	feedbackArray.clear();

	vector<Product*>::iterator itrProduct = listOfProducts.begin();
	vector<Product*>::iterator itrEndProduct = listOfProducts.end();
	for (; itrProduct != itrEndProduct; ++itrProduct)
		delete *itrProduct;
	listOfProducts.clear();
}


vector<FeedBack*> Seller::getFeedbackArray()
{
	return feedbackArray;
}

vector<Product*> Seller::getListOfProducts()
{
	return listOfProducts;
}


void Seller::AddToProductList(Product* newProduct)//Add new product for the seller
{
	listOfProducts.push_back(newProduct);
}


void Seller::addFeedbackToSeller(FeedBack* feedback)
{
	feedbackArray.push_back(feedback);
}