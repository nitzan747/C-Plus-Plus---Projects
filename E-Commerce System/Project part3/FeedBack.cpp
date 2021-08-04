#include "FeedBack.h"

FeedBack::FeedBack(const string& feedBackGiver, const Date& dateOfFeedBack, const string& message) //constructor
{
	this->feedBackGiver = feedBackGiver;
	this->dateOfFeedBack = dateOfFeedBack;
	this->message = message;
}

FeedBack::FeedBack(const FeedBack& other) //copy c'tor
{
	this->dateOfFeedBack = Date(other.dateOfFeedBack);
}


void FeedBack::setFeedBackGiverName(const string& buyerName)
{
	this->feedBackGiver = buyerName;
}

void FeedBack::setDateOfFeedBack(int day, int month, int year)
{
	dateOfFeedBack.setDate(day, month, year);
}

void FeedBack::setMessage(const string& message)
{
	this->message = message;
}

const string& FeedBack::getFeedBackGiver() const
{
	return feedBackGiver;
}

 const Date& FeedBack::getDate() const
{
	return dateOfFeedBack;
}

 const string& FeedBack::getMessage() const
{
	return message;
}

 ostream & operator<<(ostream & os, const FeedBack & feedback)//operator print feedback
{
	os << "feedback giver name is: " << feedback.feedBackGiver.c_str() << "\n" << "date of feedback is: \n" << feedback.getDate() << "the feedback is: " << feedback.message.c_str() << endl;
	return os;
}
