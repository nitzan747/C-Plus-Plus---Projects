#include "Buyer.h"

Buyer::Buyer(const string& userName, const string& password, Address* address, Order* order ) : User(userName, password, address)//c'tor default  --zero all
{
	this->order = order;
}

Buyer::Buyer(const Buyer& other) : User(other)// copy c'tor
{
	if(other.order!=NULL)
		this->order = new Order(*(other.order));
	this->orderCart = other.orderCart;
	this->shoppingCart = other.shoppingCart;
}

Buyer::Buyer(Buyer && other) : User(other)//move ctor
{
	this->order = other.order;
	other.order = NULL;
	this->orderCart = other.orderCart;
	this->shoppingCart = other.shoppingCart;
}

Buyer::~Buyer()//destructor
{	
	delete order;

	vector<Order*>::iterator itrorder = orderCart.begin();
	vector<Order*>::iterator itrEndorder = orderCart.end();
	for (; itrorder != itrEndorder; ++itrorder)
		delete *itrorder;
	orderCart.clear();

	vector<Product*>::iterator itProduct = shoppingCart.begin();
	vector<Product*>::iterator itrEndProduct = shoppingCart.end();
	for (; itProduct != itrEndProduct; ++itProduct)
		delete *itProduct;
	shoppingCart.clear();
}


void Buyer::setOrder(Order* other)
{
	this->order = other;
}

void Buyer::setOrderCart(vector<Order*> orderCart)
{
	this->orderCart = orderCart;
}

void Buyer::setShoppingCart(vector<Product*> shoppingCart)
{
	this->shoppingCart = shoppingCart;
}


Order* Buyer::getOrder()
{
	return order;
}

 vector<Order*> Buyer::GetOrderCart()
{
	return orderCart;
}

 vector<Product*>& Buyer::getShoppingCart()
{
	return shoppingCart;
}


 void Buyer::AddToOrderCart(Order* newOrder) //Add new order to orders history array
{

	orderCart.push_back(newOrder);
}

void Buyer::AddToShoppingCart(Product*  newProduct)//Add new product to shopping cart
{
	shoppingCart.push_back(newProduct);
}

void Buyer::removeProductFromShoppingCart(const int& index)
{
	shoppingCart.erase(shoppingCart.begin() + index);//deleting the index var in the array 
}


const bool Buyer:: operator>(const Buyer& other)//comparing--returns the buyer with the highest sum of shopping cart
{
	double sumFirstBuyer = 0, sumSeconBuyer = 0;
	int sizeFirstBuyerCart = this->orderCart.size();
	int sizeSecondBuyerCart = other.orderCart.size();//.GetOrderCart().size();
	for (int i = 0; i < sizeFirstBuyerCart; i++)
		sumFirstBuyer += shoppingCart[i]->getPrice();//summing up for first buyer
	for (int i = 0; i < sizeSecondBuyerCart; i++)
		sumSeconBuyer += other.shoppingCart[i]->getPrice();//summing for second
	if (sumFirstBuyer < sumSeconBuyer)
		return false;
	else//sumFirstBuyer>=sumSecondBuyer
		return true;
}