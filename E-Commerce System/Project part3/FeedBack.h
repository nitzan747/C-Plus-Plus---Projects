#ifndef FEEDBACK_H
#define FEEDBACK_H

#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <ostream>
using namespace std;

#include "Buyer.h"
#include "Date.h"

class FeedBack
{
private:
	std::string feedBackGiver;
	Date dateOfFeedBack;
	std::string message;

public:
	FeedBack() = default;
	FeedBack(const string& feedBackGiver, const Date& dateOfFeedBack, const string& message); //constructor
	FeedBack(const FeedBack& other);//copy c'tor

	void setFeedBackGiverName(const string& buyerName);
	void setDateOfFeedBack(int day, int month, int year);
	void setMessage(const string& message);

	const string& getFeedBackGiver() const;
	const Date& getDate() const ;
	const string& getMessage()const ;

	friend ostream& operator<<(ostream& os, const FeedBack& feedback);//operator print feedback
};

#endif // !FEEDBACK_H


