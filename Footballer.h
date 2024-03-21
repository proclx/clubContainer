#pragma once
#include <string>
#include <exception>
#include <iostream>

class Footballer
{
private:
	std::string name;
	std::string surname;
	unsigned scoredGoals;
	double coefficient;
public:
	~Footballer();
	Footballer();
	Footballer(const Footballer& F);

	Footballer& operator=(const Footballer& F);

	Footballer(std::string footballerName, std::string footballerSurname, unsigned goals);
	unsigned GetScoredGoals() const;
	void ChangeCoefficient(double newCoefficient);
	double GetSalary() const;
	void ReadFrom(std::istream& is = std::cin);
	void WriteTo(std::ostream& os = std::cout) const;
	bool IsBiggerThanComparedBy(const Footballer& other, double(Footballer::* method)() const) const;
	bool IsBiggerThanComparedBy(const Footballer& other, unsigned(Footballer::*func)() const) const;
};

std::ostream& operator<<(std::ostream& os, const Footballer& F);
std::istream& operator>>(std::istream& is, Footballer& F);