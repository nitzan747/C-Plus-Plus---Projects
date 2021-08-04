#ifndef Buyer_H
#define Buyer_H
#pragma warning(disable : 4996)

#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

#include "Address.h"
#include "product.h"
#include "Order.h"
#include "User.h"

class Buyer: virtual public User
{
private:
	Order* order;//pointer to order
	vector<Order*> orderCart;//array of Past Orders of the buyer 
	vector<Product*>shoppingCart;

public:
	Buyer(const string& userName, const string& password, Address* address, Order* order = NULL);//c'tor default  --zero all
	Buyer(const Buyer& other);//copy c'tor 
	Buyer(Buyer&& other);//move c'tor 
	~Buyer();//destructor

	void setOrder(Order* order);
	void setOrderCart(vector<Order*> orderCart);
	void setShoppingCart(vector<Product*> shoppingCart);

	Order* getOrder();
	vector<Order*> GetOrderCart();//shows the list of everything youve got in the cart, Once you choose an item in the cart it will ask you how many of that item would you like , once you choose it , it will be added to the sum that you need to pay , and the item will be deleted from the list
	vector<Product*>& getShoppingCart();

	void AddToShoppingCart(Product *  newProduct); //add new product to shopping cart
	void AddToOrderCart(Order* newOrder);//add finished order to order history
	void removeProductFromShoppingCart(const int& index);//remove from shopping cary the product chosen for order
	
	const bool operator>(const Buyer& other);//comparing shopping list of two buyers
};

#endif // !Buyer_H