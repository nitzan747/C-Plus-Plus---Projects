#include "BuyerAndSeller.h"

BuyerAndSeller::BuyerAndSeller(const string& userName, const string& password, Address* address) :User(userName, password, address), Buyer(userName, password, address), Seller(userName, password, address)//constructor
{

}