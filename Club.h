#pragma once
#include "Footballer.h"
#include <iostream>
#include <string>

class Club
{
private:
	std::string clubName;
	double coefficient;
	Footballer* allFootballers;
	unsigned size;
	unsigned used;
	void ChangeTwoPlayers(unsigned i);
public:
	~Club();
	Club(unsigned clubSize = 11);
	Club(const Club& C);
	Club(std::string name, unsigned clubSize, double coef = 1);
	Footballer& operator[](unsigned index);
	const Footballer& operator[](unsigned index) const;
	std::string GetClubName() const;
	void AddFootballer(const Footballer& F);
	void WriteTo(std::ostream& os = std::cout) const;
	void ReadFrom(std::istream& is);
	void SortFootballersBy(unsigned(Footballer::* method)() const, bool reverse = false);
	void SortFootballersBy(double(Footballer::* method)() const, bool reverse = false);
	unsigned FindSumOf(unsigned(Footballer::* method)() const) const;
	double FindSumOf(double(Footballer::* method)() const) const;
	void ChangeCoefficient(double newCoef, bool setNewCoefForAll = true);
	struct DataAboutClub
	{
		std::string DA_clubName;
		unsigned DA_coefficient;
		unsigned DA_size;
	};
	friend Club** ReadMultipleClubsFromFile(const DataAboutClub* dataAboutClubs, unsigned length, std::istream& is);
};

std::istream& operator>>(std::istream& is, Club& C);
std::ostream& operator<<(std::ostream& os, const Club& C);

std::istream& operator>>(std::istream& is, Club::DataAboutClub& DA);

Club& MaxClub(unsigned(Footballer::* method)() const, Club** clubs, unsigned length);
Club& MaxClub(double(Footballer::* method)() const, Club** clubs, unsigned length);