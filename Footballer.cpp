#include "Footballer.h"

Footballer::~Footballer()
{
}

Footballer::Footballer()
	: name(""), surname(""), scoredGoals(0), coefficient(1)
{
}

Footballer::Footballer(const Footballer& F)
{
	name = F.name;
	surname = F.surname;
	coefficient = F.coefficient;
	scoredGoals = F.scoredGoals;
}

Footballer& Footballer::operator=(const Footballer& F)
{
	name = F.name;
	surname = F.surname;
	coefficient = F.coefficient;
	scoredGoals = F.scoredGoals;
	return *this;
}

Footballer::Footballer(std::string footballerName, std::string footballerSurname, unsigned goals)
	: name(footballerName), surname(footballerSurname), scoredGoals(goals), coefficient(1)
{
}

unsigned Footballer::GetScoredGoals() const
{
	return scoredGoals;
}

void Footballer::ChangeCoefficient(double newCoefficient)
{
	if (newCoefficient < 0)
	{
		throw(std::exception("Bad coefficient value"));
	}
	else
	{
		coefficient = newCoefficient;
	}
}

double Footballer::GetSalary() const
{
	return scoredGoals * coefficient;
}

void Footballer::ReadFrom(std::istream& is)
{
	is >> name;
	is >> surname;
	is >> scoredGoals;
	coefficient = 1;
}

void Footballer::WriteTo(std::ostream& os) const
{
	os << "Footballer: " << name << ' ' << surname << " scored goals: " 
		<< scoredGoals << " salary: " << GetSalary() << '\n';
}

bool Footballer::IsBiggerThanComparedBy(const Footballer& other, double(Footballer::* method)() const) const
{
	return (this->*method)() > (other.*method)();
}

bool Footballer::IsBiggerThanComparedBy(const Footballer& other, unsigned(Footballer::* method)() const) const
{
	return (this->*method)() > (other.*method)();
}

std::ostream& operator<<(std::ostream& os, const Footballer& F)
{
	F.WriteTo(os);
	return os;
}

std::istream& operator>>(std::istream& is, Footballer& F)
{
	F.ReadFrom(is);
	return is;
}
