#include "Date.h"

Date::Date(const int& day,const int& month,const int& year) // constructor
{
	setDate(day, month, year);
}

Date::Date(const Date& other) // copy c'tor
{
	day = other.day;
	month = other.month;
	year = other.year;
}


bool Date::setDay(int day)
{
	if (!checkDay(day)) // check if day is legal
		return false;
	this->day = day;
	return true;
}

bool Date::setMonth(int month)
{
	if (!checkMonth(month)) // check if month is legal
		return false;
	this->month = month;
	return true;
}

bool Date::setYear(int year)
{
	if (!checkYear(year)) // check if year is legal
		return false;
	this->year = year;
	return true;
}


const int& Date::getDay() const
{
	return day;
}

const int& Date::getMonth() const
{
	return month;
}

const int& Date::getYear() const
{
	return year;
}


bool Date::checkDay(const int& day) const  // check if day is legal
{
	if (day >= 1 && day <= 31)
		return true;
	return false;
}

bool Date::checkMonth(const int& month) const  // check if month is legal
{
	if (month >= 1 && month <= 12)
		return true;
	return false;
}

bool Date::checkYear(const int& year) const // check year day is legal
{
	if (year >= 2000 && year <= 2020)
		return true;
	return false;
}

void Date::setDate(const int& day,const int& month,const int& year) // insert all information to date
{
	this->day = day;
	this->month = month;
	this->year = year;
}

ostream& operator<<(ostream & os,const Date & date) //operator print date
{
	os << "Year is :" << date.getYear() << "\n" << "Month is: " << date.getMonth() << "\n" << "Day is: " << date.getDay() << endl;
	return os;
}
