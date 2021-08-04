#include "E-CommerceSystem.h"
#include <string>
static void printMenu();
static bool checkChoice(int choice);
static bool checkLettersAndNumbersOnly(const string& str);
static bool passwordInCorrectLength(const string& pass);
static bool isStrCorrect(const string& str);
static bool isLetter(char c);
static bool isHouseNumberLegal(int num);
static void checkDay(int day);
static void checkMonth(int month);
static void checkYear(int year);


System::System()//c'tor
{

}

System::~System() //destructor
{
	vector<User*>::iterator itr = usersArray.begin();
	vector<User*>::iterator itrEnd = usersArray.end();
	for (; itr != itrEnd; ++itr)
		delete *itr;
	usersArray.clear();
}


void System::setUsersArray(vector<User*> user)
{
	this->usersArray = user;//will point to the new array
}


vector<User*> System::getUsersArray()
{
	return usersArray;
}


void System::systemRun()
{
	int choice = 0;
	string fileName;
	cout << "Please enter the file name: " << endl;
	getline(cin, fileName);

	ifstream inFile(fileName);
	if (!inFile.fail())//check if file exist 
		getInfoFromFile(inFile);
	else
		cout << "The file has not found" << endl;
	
	while (choice != EXIT)
	{
		printMenu();
		cin >> choice;
		cleanBuffer();
		if (!checkChoice(choice)) // check if the choice is legal
		{
			cout << "You must choose an option between 1 to 14" << endl;
			printMenu();
			exit(-1);
		}
		else
		{
			switch (choice)
			{
			case 1:
				addNewBuyer();
				break;
			case 2:
				addNewSeller();
				break;
			case 3:
				addProductToSeller();
				break;
			case 4:
				addFeedBackToSeller();
				break;
			case 5:
				addProductToShoppingCart();
				break;
			case 6:
				MakeAnOrder();
				break;
			case 7:
				payForOrder();
				break;
			case 8:
				showAllBuyers();
				break;
			case 9:
				showAllSellers();
				break;
			case 10:
				showAllBuyersAndSellers();
				break;
			case 11:
				showAllUsersOfCertainType();
				break;
			case 12:
				getTheNameOfTheProduct();
				break;
			case 13:
				checkOperators();
				break;
			case 14:
				writeInfoToFile(fileName);
				break;//for exit
			default:
				break;
			}
		}
	}
}


void System::writeInfoToFile(const string& fileName)
{
	ofstream outFile(fileName, ios::trunc);

	outFile << usersArray.size() << endl;
	for (int i = 0; i < usersArray.size(); i++)
	{
		outFile << typeid(*(usersArray[i])).name() + 6 << " " << *(usersArray[i]) << endl;
	}
	outFile.close();
}

void System::getInfoFromFile(ifstream& inFile)
{
	int logSize, i;
	string userName, password, type;
	Address address("tempCountry", "tempCity", "tempStreet", 1);

	inFile >> logSize; //Get from file the amount of users

	for (i = 0; i < logSize; i++)
	{
		inFile >> type; //Get from file the type of user
		inFile >> userName >> password >> address; //Get from file the user's info
		if (type == typeid(BuyerAndSeller).name() + 6) //The user is a buyer and seller
			usersArray.push_back(new BuyerAndSeller(userName, password, &address));
		else if (type == typeid(Seller).name() + 6)//The user is a seller
			usersArray.push_back(new Seller(userName, password, &address));
		else if (type == typeid(Buyer).name() + 6)//The user is a 
			usersArray.push_back(new Buyer(userName, password, &address));		
	}
	inFile.close();
}

static void printMenu()
{
	cout << endl << "----------------------------------------------------" << endl;
	cout << "Please choose of the following options: " << endl;
	cout << "To add buyer PRESS 1" << endl;
	cout << "To add seller PRESS 2" << endl;
	cout << "To add product for seller PRESS 3" << endl;
	cout << "To add feedback for seller PRESS 4" << endl;
	cout << "To add product for shopping cart PRESS 5" << endl;
	cout << "To make an order PRESS 6" << endl;
	cout << "To pay for order PRESS 7" << endl;
	cout << "To show all buyers PRESS 8" << endl;
	cout << "To show all sellers PRESS 9" << endl;
	cout << "To show all buyers and sellers PRESS 10" << endl;
	cout << "To show all users of certain type PRESS 11" << endl;
	cout << "To search for products PRESS 12" << endl;
	cout << "To check operators press 13 " << endl;
	cout << "For EXIT PRESS 14" << endl;
}

static bool checkChoice(int choice)//check this
{
	if (choice >= 1 && choice <= 14)
		return true;
	return false;
}

void System::cleanBuffer()//cleans the buffer from enter etc..
{
	int c;
	do
	{
		c = getchar();
	} while (c != '\n');
}

const int& System::logIn(string& userName, string& passWord, int& index)
{
	cout << "Please enter your user name: " << endl;
	getline(cin, userName);
	int user = checkIfUserNameExist(userName, index);

	if (user == BUYER)//check if username exist
	{
		if (!checkIfUserPasswordCorrect(index, passWord))
		{
			cout << "Password is incorrect" << endl;
			return NONE;
		}
		return BUYER;
	}
	else if (user == SELLER)
	{
		if (!checkIfUserPasswordCorrect(index, passWord))
		{
			cout << "Password is incorrect  " << endl;
			return NONE;
		}
		return SELLER;
	}
	else if (user == BUYER_AND_SELLER)
	{
		if (!checkIfUserPasswordCorrect(index, passWord))
		{
			cout << "Password is incorrect  " << endl;
			return NONE;
		}
		return BUYER_AND_SELLER;
	}
	else//username dosent exist 
	{
		cout << "Username dosent exist" << endl;
		return NONE;
	}
}

int System::checkIfUserNameExist(const string& userName, int& index)//runs on both seller and buyer,checks if the username inserted for log in is right 
{
	int i;
	for (i = 0; i < usersArray.size(); i++) //check if seller
	{
		if (userName == usersArray[i]->getUserName())
		{
			index = i;
			if (typeid(*usersArray[i]) == typeid(Buyer))
				return BUYER;
			else if (typeid(*usersArray[i]) == typeid(Seller))
				return SELLER;
			else
				return BUYER_AND_SELLER;
		}		
	}
	return NONE;

	for (i = 0; i < usersArray.size(); i++) // check if buyer
	{
		if (userName == usersArray[i]->getUserName())
		{
			index = i;
			return BUYER;
		}
	}
	return NONE;
}

bool System::checkIfUserPasswordCorrect(int index, string& password)
{
	bool answer = false;
	cout << "Please enter your password: " << endl;
	getline(cin, password);

	if (index < usersArray.size())
		if (usersArray[index]->getPassword() == password)
			answer = true;
	return answer;
}

void System::addNewBuyer() //seif 1
{
	int onlyBuyer;
	string tempName;
	string tempPassword;//const
	Address* tempAddress;

	cout << "If you want to be also seller press 0, else press 1" << endl;
	cin >> onlyBuyer;
	cleanBuffer();

	tempAddress = getInfoForNewAllocationOfSellerOrBuyer(tempName, tempPassword);//copy ctor
	if (!onlyBuyer)
	{
		BuyerAndSeller tempBuyerSeller(tempName, tempPassword, tempAddress);
		(*this) += tempBuyerSeller;//add buyer and seller to the usersArray
	}
	else
	{
		Buyer tempBuyer(tempName, tempPassword, tempAddress);
		(*this) += tempBuyer;//add buyer to the usersArray
	}	
}

Address* System::getInfoForNewAllocationOfSellerOrBuyer(string& tempName,  string&  tempPassword)
{
	Address* tempAddress;
	cout << "Choose your username, not more than 20 chars: " << endl;
	getline(cin,tempName);

	while (!checkIfNameIsTaken(tempName) || !checkLettersAndNumbersOnly(tempName))
	{
		cout << "Please enter a different username" << endl;
		getline(cin,tempName);
	}

	cout << "Please enter your password, must contain exactly 8 characters   " << endl;
	getline(cin,tempPassword);
	
	while (!passwordInCorrectLength(tempPassword))
	{
		cout << "Password doesnt contain 8 characters, please try again: " << endl;
		getline(cin,tempPassword);
	}
	tempAddress = new Address(addressInfo());//insert address
	return tempAddress;
}

bool System::checkIfNameIsTaken(const string&  name)//checks if the new register can use the username he chose or not.
{
	int i;
	for (i = 0; i < usersArray.size(); i++) //check if name is taken by other user
	{
		if (name == usersArray[i]->getUserName())
			return false;
	}
	return true;
}

static bool checkLettersAndNumbersOnly(const string& str)
{
	int i, size = str.length();
	for (i = 0; i < size; i++)
	{
		if ((str[i] < '0') || (str[i] > '9' && str[i] < 'A') || (str[i] > 'Z' && str[i] < 'a') || (str[i] > 'z'))//checking if there is any char that dosent contain a digit or letter 
			return false;
	}
	cout << endl;
	return true;
}

static bool passwordInCorrectLength(const string& pass)
{
	int size = pass.length();
	if (size == PASSWORD_LENGTH-1)
		return true;
	return false;
}

Address System::addressInfo()
{
	string country, city, street;
	int houseNumber;

	cout << "Please enter your country: " << endl;
	getline(cin, country);
	while (!isStrCorrect(country))
	{
		cout << "Country is incorrect, please enter again " << endl;
		getline(cin, country);
	}

	cout << "Please enter your City: " << endl;
	getline(cin, city);
	while (!isStrCorrect(city))
	{
		cout << "City is incorrect, please enter again " << endl;
		getline(cin, city);
	}

	cout << "Please enter your street: " << endl;
	getline(cin, street);
	while (!isStrCorrect(street))
	{
		cout << "Street is incorrect, please enter again " << endl;
		getline(cin, street);
	}

	cout << "Please enter your house number:" << endl;
	cin >> houseNumber;
	while (!isHouseNumberLegal(houseNumber))
	{
		cout << "House number is incorrect, please enter again " << endl;
		cin >> houseNumber;
	}
	return Address(country, city, street, houseNumber);
}

static bool isStrCorrect(const string& str)
{
	int i = 0 ;
	while (str[i] != '\0')
	{
		if (!isLetter(str[i]))
			return false;
		i++;
	}
	return true;
}

static bool isLetter(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a') && (c <= 'z')) // c is capital letter or small letter
		return true;
	return false;
}

static bool isHouseNumberLegal(int num)//Check if house number is not negative or 0
{
	if (num <= 0)
		return false;
	return true;
}


void System::addNewSeller()//seif 2
{
	int onlySeller;
	string tempName;
	string tempPassword;
	Address* tempAddress;

	cout << "If you want to be also buyer press 0, else press 1" << endl;
	cin >> onlySeller;
	cleanBuffer();

	tempAddress = getInfoForNewAllocationOfSellerOrBuyer(tempName, tempPassword);
	
	if (!onlySeller)
	{
		BuyerAndSeller tempBuyerSeller(tempName, tempPassword, tempAddress);
		(*this) += tempBuyerSeller;//add buyer and seller to the usersArray
	}
	else
	{
		Seller tempSeller(tempName, tempPassword, tempAddress);
		(*this) += tempSeller;//add seller to the usersArray	
	}
}


void System::addProductToSeller() // seif 3
{
	string userName;
	string passWord;
	int indexOfSeller;
	int connected  = logIn(userName, passWord, indexOfSeller);

	if (connected == BUYER  )	
		cout << "Only seller can add new Product !" << endl;
	else if (connected == SELLER || connected == BUYER_AND_SELLER)//connected to seller 
	{
		Product* product = new Product(insertInfoForProduct(dynamic_cast<Seller*>(usersArray[indexOfSeller])));
		dynamic_cast<Seller*>(usersArray[indexOfSeller])->AddToProductList(product);
	}	
}

Product System::insertInfoForProduct(Seller* pSeller)
{
	string name;
	int category;
	double price;
	cout << "Please enter name for product: " << endl;
	getline(cin, name);
	cout << "Please choose product category: "<< endl << "for children press 0 " << endl << "for Electricty press 1" << endl << "for Clothing press 2 " << endl << "for  Office press 3 " << endl;
	cin >> category;
	while (category != 0 && category != 1 && category != 2 && category != 3)
	{
		cout << "Category incorrect, please enter again: " << endl;
		cin >> category;
	}
	cout << "Please enter the price of the product: " << name << endl;
	cin >> price;
	while (price <= 0)
	{
		cout << "Price is illegal, please enter again: " << name << endl;
		cin >> price;
	}
	return (Product(name, Product::eCategory(category), price, pSeller));//returns as product--ctor
}


void System::addFeedBackToSeller() //seif 4
{
	string userName;
	string password;
	int indexOfBuyer;
	int logSizeofOrderCart, i;
	vector<Order*> orderCart;
	int connected = logIn(userName, password, indexOfBuyer);

	if (connected == NONE)
		cout << "Could not log In" << endl;
	else if (connected == SELLER)
		cout << "Only Buyer can add feedback !" << endl;
	else
	{
		logSizeofOrderCart = dynamic_cast<Buyer*>(usersArray[indexOfBuyer])->GetOrderCart().size();
		if (logSizeofOrderCart == 0)
			cout << "You must purchase product before adding feedback" << endl;
		else
		{
			for (i = 0; i < logSizeofOrderCart; i++)			
				orderCart.push_back(dynamic_cast<Buyer*>(usersArray[indexOfBuyer])->GetOrderCart()[i]);
			
			Seller* seller = chooseSellerForFeedBack(orderCart, logSizeofOrderCart);
			if (seller != NULL)			
				createFeedBack(seller, userName);
		}
	}
}

Seller* System::chooseSellerForFeedBack(vector<Order*> orderCart, int& size)
{
	int orderIndex;
	Array<Product> productList;
	string productName;
	cout << "Please enter the name of the product for feedback: " << endl;
	getline(cin, productName);

	int productIndex = searchForProduct(orderCart, size, productName, orderIndex);
	if (productIndex != NONE)
	{
		productList = orderCart[orderIndex]->getProductsArray();
		return productList.getArrByIndex(productIndex).getSeller();
	}
	else
		cout << "Product has not been found" << endl;
	return NULL;
}

int System::searchForProduct(vector<Order*> orderCart, int size, const string& productName, int& orderIndex)//Search the product at the sellers products array
{
	int i, j, sizeOfProductArray;
	for (i = 0; i < size; i++)
	{
		sizeOfProductArray = orderCart[i]->getProductsArray().getLogSize();

		for (j = 0; j < sizeOfProductArray; j++)
		{
			if (orderCart[i]->getProductsArray().getArrByIndex(j).getName() == productName)
			{
				orderIndex = i;
				return j;
			}
		}
	}
	return NONE;
}

void System::createFeedBack(Seller* seller, const string& buyerName)
{
	string message;
	int day, month, year;
		
	cout << "Please enter today's date: " << endl;
	cout << "Day: ";
	cin >> day;
	checkDay(day);

	cout << endl << "Month: ";
	cin >> month;
	checkMonth(month);

	cout << endl << "Year: ";
	cin >> year;
	checkYear(year);
	
	Date date(day, month, year);

	cout << endl << "Please enter your feedback: " << endl;
	cleanBuffer();
	getline(cin,message);

	FeedBack* feedback = new FeedBack(buyerName, date, message);
	seller->addFeedbackToSeller(feedback);
}

static void checkDay(int day)
{
	while (day < 1 || day > 31)
	{
		cout << "Day is not legal, please enter again" << endl;
		cin >> day;
	}
}

static void checkMonth(int month)
{
	while (month < 1 || month > 12)
	{
		cout << "Month is not legal, please enter again" << endl;
		cin >> month;
	}
}

static void checkYear(int year)
{
	while (year <2000 || year > 2020)
	{
		cout << "Year is not legal, please enter again" << endl;
		cin >> year;
	}
}


void System::addProductToShoppingCart()//seif 5
{
	string userName;
	string passWord;
	int indexOfBuyer;
	string SellerName;
	Product *product;
	int indexOfSeller, connected;
	string productName;

	connected = logIn(userName, passWord, indexOfBuyer);
	if (connected == NONE)	
		cout << "Could not connect to your account" << endl;
	else if (connected == SELLER)
		cout << "Only buyer can add products to his shopping cart ! " << endl;
	else //you are buyer or buyer and seller
	{
		cout << "Please enter the name of the seller:" << endl;
		getline(cin,SellerName);
		if (userName== SellerName )
			cout << "Can't purchase your own product!" << endl;
		else
		{
			cout << "Please enter the name of the product: " << endl;
			getline(cin,productName);

			indexOfSeller = searchForSeller(SellerName);
			if (indexOfSeller != NONE)
			{
				product = (searchForProductOfSpecificSeller(productName, dynamic_cast<Seller*>(usersArray[indexOfSeller])));//hadar not sure i did another allocation Here to what returnd from the function so the new vector will work properly 
				if (product)
				{
					dynamic_cast<Buyer*>(usersArray[indexOfBuyer])->AddToShoppingCart(product);//adding the product to the exact buyer who is currently using the system(logged In)
					cout << "Product added" << endl;
				}			
			}
			else
				cout << "Seller has not been found" << endl;
		}
	}
}

int System::searchForSeller(const string& name)
{
	int index = NONE;
	for (int i = 0; i < usersArray.size(); i++)
	{
		if (name == this->usersArray[i]->getUserName())
			index = i;
	}
	return index;
}

Product* System::searchForProductOfSpecificSeller(const string& productName, Seller* seller)
{
	int index = NONE;
	vector<Product*> productList = seller->getListOfProducts();

	for (int i = 0; i < productList.size(); i++)
		if (productList[i]->getName() == productName)
			index = i;
	if (index == NONE)
	{
		cout << "Product doesnt exist for this seller " << endl;
		return NULL;
	}
	return productList[index];
}


void System::MakeAnOrder()//seif 6
{
	string userName;
	string passWord;
	int indexOfBuyer, sizeOfShoppingCart;
	int connected;
	vector <Product*> ShoppingCart;

	connected = logIn(userName, passWord, indexOfBuyer);//connect to the system as Buyer
	if (connected == NONE)
		cout << "Could not log in" << endl;
	else if (connected == SELLER)
		cout << "Only buyer can make an order! " << endl;
	else //you are buyer or buyer and seller
	{
		sizeOfShoppingCart = dynamic_cast<Buyer*>(usersArray[indexOfBuyer])->getShoppingCart().size();

		if (sizeOfShoppingCart == 0)
			cout << "No products in shopping cart" << endl;
		else if (dynamic_cast<Buyer*>(usersArray[indexOfBuyer])->getOrder() != NULL)
			cout << "The last order is not completed" << endl;
		else //you can start the order
		{
			ShoppingCart = dynamic_cast<Buyer*>(usersArray[indexOfBuyer])->getShoppingCart();
			addChosenProductsToOrder(sizeOfShoppingCart, dynamic_cast<Buyer*>(usersArray[indexOfBuyer]));
		}
	}
}

void System::addChosenProductsToOrder(int shoppingCartSize, Buyer* buyer)
{
	int i;
	bool answer;
	Order* tempOrder;

	if (buyer->getOrder()== NULL)
	{
		tempOrder = new Order(buyer->getUserName());
		buyer->setOrder(tempOrder);//allocate
	}
	
	for (i = 0; i <  buyer->getShoppingCart().size(); i++)
	{
		cout << "The product is : " << buyer->getShoppingCart()[i]->getName() << endl << "Would you like to add it to your order ?" << endl << "Press 1 for yes, 0 for no " << endl;
		cin >> answer;
		if (answer == true)
		{
			(*buyer).getOrder()->addProduct(*buyer->getShoppingCart()[i]);
			buyer->removeProductFromShoppingCart(i);
			cout << "Product added" << endl;			
			i--;
		}
	}
}


void System::payForOrder() //seif 7
{
	string userName;
	string passWord;
	int indexOfBuyer;
	int connected;
	Order* order;

	connected = logIn(userName, passWord, indexOfBuyer);//connect to the system as Buyer
	if (connected == NONE)
		cout << "Could not log in" << endl;
	else if (connected == SELLER)
		cout << "Only buyer can make an order! " << endl;
	else //you are buyer or buyer and seller
	{
		order = dynamic_cast<Buyer*>(usersArray[indexOfBuyer])->getOrder();
		if (order != NULL)
			finishOrder(order, dynamic_cast<Buyer*>(usersArray[indexOfBuyer]));
		else
			cout << "You payed for all your orders :)" << endl;
	}
}

void System::finishOrder(Order* order, Buyer* buyer)
{
	double sumCost, inputCost;

	order->updateTotalSumCost();
	sumCost = order->getTotalSumCost();

	cout << "The total sum cost of order is: " << sumCost << " please enter the amount needed" << endl;
	cin >> inputCost;
	if (inputCost >= sumCost)
	{
		buyer->AddToOrderCart(order);
		buyer->setOrder(NULL);
		cout << "Your purchase has been confirmed!" << endl;
	}
	else
		cout << "Insufficent funds, order has not been completed " << endl;
}


void System::showAllBuyers()//seif 8
{
	if (usersArray.size() == 0)
		cout << "No users!" << endl;
	int countBuyers = 0;
	for (int i = 0; i < usersArray.size(); i++)
	{
		if (typeid(*(usersArray[i])) == typeid(Buyer))
		{
			cout << "Username number : " << i + 1 << "'s buyer is : " << this->usersArray[i]->getUserName() << " and his password is : " << this->usersArray[i]->getPassword() << endl;
			countBuyers++;
		}
	}
	if (countBuyers == 0) // no buyers 
		cout << "No buyers!" << endl;
}


void System::showAllSellers()//seif 9 
{
	if (usersArray.size() == 0)
		cout << "No users!" << endl;
	int countSellers = 0;
	for (int i = 0; i < usersArray.size(); i++)
	{
		if (typeid(*(usersArray[i])) == typeid(Seller))
		{
			cout << "Username number : " << i + 1 << "'s seller is : " << this->usersArray[i]->getUserName() << " and his password is : " << this->usersArray[i]->getPassword() << endl;
			countSellers++;
		}
	}
	if (countSellers == 0) // no sellers
		cout << "No sellers!" << endl;
}


void System::showAllBuyersAndSellers()//seif 10
{
	if (usersArray.size() == 0)
		cout << "No users!" << endl;
	int countBuyersAndSellers = 0;
	for (int i = 0; i < usersArray.size(); i++)
	{
		if (typeid(*(usersArray[i])) == typeid(BuyerAndSeller))
		{
			cout << "Username number : " << i + 1 << "   buyerAndSeller name is : " << this->usersArray[i]->getUserName() << " and his password is : " << this->usersArray[i]->getPassword() << endl;
			countBuyersAndSellers++;
		}
	}
	if (countBuyersAndSellers == 0) // no buyer and sellers
		cout << "No buyer and sellers!" << endl;
}


void System::showAllUsersOfCertainType()//seif 11
{
	int user;
	cout << "Please enter the users you are looking for: \n" <<  "0 for sellers \n" << "1 for buyers \n" << "2 for buyer and sellers " << endl;
	cin >> user;
	if (user == SELLER)
		showAllSellers();
	else if (user == BUYER)
		showAllBuyers();
	else if (user == BUYER_AND_SELLER)
		showAllBuyersAndSellers();
	else
		cout << "Your choice is illegal" << endl;
}


void System::getTheNameOfTheProduct()// seif 12
{
	string productName;

	cout << "enter the name of the product you are searching for : " << endl;
	getline(cin, productName);
	SearchForProductExistence(productName);
}

void System::SearchForProductExistence(const string& productName) 
{
	bool productExist = false;
	for (int i = 0; i < usersArray.size(); i++)
	{
		if (typeid(*usersArray[i]) == typeid(Seller) || typeid(*usersArray[i]) == typeid(BuyerAndSeller))
		{
			vector<Product*> productListTemp = dynamic_cast<Seller*>(usersArray[i])->getListOfProducts();
			if (!productListTemp.empty())
				for (int j = 0; j < productListTemp.size(); j++)
				{
					if (productName == productListTemp[j]->getName())//checks if found a product with the exact name
					{
						cout << "The Seller number is : " << i + 1 << ", which his name is: " << this->usersArray[i]->getUserName() << " has the product, the price is: " << productListTemp[j]->getPrice() << endl;
						productExist = true;
					}
				}
		}
	}
	if(!productExist)
		cout << "The product has not been found" << endl;
}


void System::checkOperators()//seif 13
{
	testOperatorCout();
	testOperatorCompare();
}

void System::testOperatorCout()
{
	cout << "TEST OF OPERATOR << : " << endl;
	Date testDate(2, 6, 2020);//test
	Address testAddress("testCountry", "testCity", "testStreet", 11);//test
	FeedBack testFeedback("feedBackGiverTest", testDate, "this is a Test message!!");
	cout << "-------------------------------------" << endl;
	cout << "test DATE operator" << endl;
	cout << testDate;
	cout << "-------------------------------------" << endl;
	cout << "test ADDRESS operator" << endl;
	cout << &testAddress;
	cout << "-------------------------------------" << endl;
	cout << "test FEEDBACK operator" << endl;
	cout << testFeedback;//test all of operators << made 
	cout << "-------------------------------------" << endl;
}

void System::testOperatorCompare()
{	
	cout << "TEST OF OPERATOR > : " << endl;
	int i;
	double priceTestOne = 0, priceTestTwo = 0;
	Product::eCategory category = (Product::eCategory)0;
	Address* address = new Address("testCountry", "testCity", "testStreet", 1);

	Buyer testBuyer1("hadar", "12345678", address);
	Buyer testBuyer2("nitzan", "12345678", address);
	Seller* testSeller=new Seller("seller", "12345678", address);
	vector<Product*> shopingCartforBuyerOne;
	vector<Product*> shopingCartforBuyerTwo;
	for (i = 0; i < testSize; i++)
	{
		priceTestOne += 2;
		priceTestTwo += 1;
		shopingCartforBuyerOne.push_back(new Product("testproductBuyerOne", category, priceTestOne, testSeller));
		shopingCartforBuyerTwo.push_back(new Product("testproductBuyerTwo", category, priceTestTwo, testSeller));//second buyer will have a smaller sum 
	}

	testBuyer1.setShoppingCart(shopingCartforBuyerOne);
	testBuyer2.setShoppingCart(shopingCartforBuyerTwo);

	printTest(testBuyer1, testBuyer2);
	delete testSeller;
}


void System:: printTest(Buyer& buyerOne, Buyer& buyerTwo)
{
	cout << "if the test works, buyer number one should be bigger then buyer two" << endl;
	cout << "is buyer one bigger then buyer two??" << endl;
	if (buyerOne > buyerTwo == true)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;
	cout << "-------------------------------------" << endl;
	cout << "is buyer two bigger then buyer One??" << endl;

	if (buyerOne > buyerTwo == false)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;

}

void System::operator+=(const Buyer& other)
{
	usersArray.push_back(new Buyer(other));
}

void System::operator+=(const Seller& other)
{
	usersArray.push_back(new Seller(other));
}

void System::operator+=(const BuyerAndSeller& other)
{
	usersArray.push_back(new BuyerAndSeller(other));
}