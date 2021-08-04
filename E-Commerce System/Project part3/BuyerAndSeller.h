#ifndef BuyerAndSeller_H
#define BuyerAndSeller_H

#include "Buyer.h"
#include "Seller.h"

class BuyerAndSeller : public Buyer, public Seller
{
public:
	BuyerAndSeller( const string& userName, const string& password, Address* address);//constructor	
};

#endif // ! BuyerAndSeller_H
