#ifndef Date_H
#define Date_H

#pragma warning(disable : 4996)
#include <ostream>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

class Date
{
private:
	int day;
	int month;
	int year;

public:
	Date() = default;
	Date(const int& day,const  int& month,const int& year);	//constructor
	Date(const Date& other); // copy c'tor

	bool setDay(int day);
	bool setMonth(int month);
	bool setYear(int year);

	const int& getDay() const;
	const int& getMonth() const;
	const int& getYear() const;

	bool checkDay(const int& day) const ;
	bool checkMonth(const int& month) const ;
	bool checkYear(const int& year) const ;

	void setDate(const int& day, const int& month, const int& year);
	friend ostream& operator<<(ostream& os, const Date& date); //operator print date
};

#endif // !Date_H
