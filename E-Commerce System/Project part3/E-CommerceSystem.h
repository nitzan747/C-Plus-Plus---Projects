#ifndef ECommercySystem_H
#define ECommercySystem_H
#pragma warning(disable : 4996)

#include <ostream>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Definitions.h"
#include "Seller.h"
#include "BuyerAndSeller.h"
using namespace std;

class System
{
private:
	vector<User*> usersArray;

public:
	System(); //constructor
	~System(); //destructor
	
	void setUsersArray(vector<User*> user);
	
	vector<User*> getUsersArray();

	void systemRun();
	void writeInfoToFile(const string& fileName);
	void getInfoFromFile(ifstream& inFile);
	void cleanBuffer();
	const  int& logIn(string& userName, string& passWord, int& index);
	int checkIfUserNameExist(const string& userName, int& index);
	bool checkIfUserPasswordCorrect(int index, string& password);

	void addNewBuyer(); //seif 1
	Address* getInfoForNewAllocationOfSellerOrBuyer(string& tempName, string&  tempPassword);
	bool checkIfNameIsTaken(const string& name);
	Address addressInfo();

	void addNewSeller(); //seif 2
	
	void addProductToSeller();//seif 3
	Product insertInfoForProduct(Seller* pSeller);

	void addFeedBackToSeller(); //seif 4
	Seller* chooseSellerForFeedBack(vector<Order*> orderCart, int &size);
	void createFeedBack(Seller* seller, const string& buyerName);
	int searchForProduct(vector<Order*> orderCart, int size, const string& productName, int&orderIndex);

	void addProductToShoppingCart(); //seif 5
	int searchForSeller(const string& name);
	Product* searchForProductOfSpecificSeller(const string& productName, Seller* seller);

	void MakeAnOrder();//seif 6 
	void addChosenProductsToOrder(int shoppingCartSize, Buyer* buyer);

	void payForOrder();//seif 7
	void finishOrder(Order* order, Buyer* buyer);

	void showAllBuyers();// seif 8

	void showAllSellers();// seif 9

	void showAllBuyersAndSellers();//seif 10

	void showAllUsersOfCertainType();//seif 11

	void getTheNameOfTheProduct(); //seif 12
	void SearchForProductExistence(const string& productName);

	void checkOperators();//seif 13
	void testOperatorCout();
	void testOperatorCompare();
	void printTest(Buyer& buyerOne, Buyer& buyerTwo);

	void operator+=(const Buyer& other);//Add new buyer to users array
	void operator+=(const Seller& other);//Add new seller to users array
	void operator+=(const BuyerAndSeller& other);//Add new buyer seller to users array
};

#endif // !E-CommerceSystem_H
