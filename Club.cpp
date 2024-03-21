#include "Club.h"

Club::~Club()
{
	delete[] allFootballers;
}

Club::Club(unsigned clubSize)
	: used(0), size(clubSize), clubName("Default name"), coefficient(1), allFootballers(new Footballer[clubSize])
{
}

Club::Club(const Club& C)
	: used(C.used), size(C.size), clubName(C.clubName), coefficient(C.coefficient), allFootballers(new Footballer[C.size])
{
	for (unsigned i = 0; i < used; ++i)
	{
		allFootballers[i] = Footballer(C.allFootballers[i]);
	}
}

Club::Club(std::string name, unsigned clubSize, double coef)
	: clubName(name), size(clubSize), coefficient(coef), used(0), allFootballers(new Footballer[clubSize])
{
}

Footballer& Club::operator[](unsigned index)
{
	if (index >= used)
	{
		throw(std::out_of_range{ "Club::operator[]::Bad value" });
	}
	else
	{
		return allFootballers[index];
	}
}

const Footballer& Club::operator[](unsigned index) const
{
	if (index >= used)
	{
		throw(std::out_of_range{ "Club::operator[]::Bad value" });
	}
	else
	{
		return allFootballers[index];
	}
}

std::string Club::GetClubName() const
{
	return clubName;
}

void Club::AddFootballer(const Footballer& F)
{
	if (used >= size)
	{
		throw(std::out_of_range{ "Club::AddFootballer::Lack of free space in array" });
	}
	else
	{
		allFootballers[used] = F;
		allFootballers[used].ChangeCoefficient(coefficient);
		++used;
	}
}

void Club::WriteTo(std::ostream& os) const
{
	os << "Club: " << clubName << std::endl
		<< "Coefficient: " << coefficient << std::endl
		<< "Size: " << size << std::endl
		<< "Used: " << used << std::endl;
	for (unsigned i = 0; i < used; ++i)
	{
		allFootballers[i].WriteTo(os);
	}
}

void Club::ChangeTwoPlayers(unsigned i)
{
	Footballer temp{ allFootballers[i] };
	allFootballers[i] = allFootballers[i + 1];
	allFootballers[i + 1] = temp;
}

void Club::SortFootballersBy(unsigned(Footballer::* method)() const, bool reverse)
{
	if (not reverse)
	{
		for (unsigned i = 0; i < used - 1; ++i)
		{
			if (allFootballers[i].IsBiggerThanComparedBy(allFootballers[i + 1], method))
			{
				ChangeTwoPlayers(i);
				int j = i - 1;
				while (j >= 0)
				{
					if (allFootballers[j].IsBiggerThanComparedBy(allFootballers[j + 1], method))
					{
						ChangeTwoPlayers(j);
					}
					--j;
				}
			}
			else
			{
				continue;
			}
		}
	}
	else
	{
		for (unsigned i = 0; i < used - 1; ++i)
		{
			if (not allFootballers[i].IsBiggerThanComparedBy(allFootballers[i + 1], method))
			{
				ChangeTwoPlayers(i);
				int j = i - 1;
				while (j >= 0)
				{
					if (not allFootballers[j].IsBiggerThanComparedBy(allFootballers[j + 1], method))
					{
						ChangeTwoPlayers(j);
					}
					--j;
				}
			}
			else
			{
				continue;
			}
		}
	}
}

void Club::SortFootballersBy(double(Footballer::* method)() const, bool reverse)
{
	if (not reverse)
	{
		for (unsigned i = 0; i < used - 1; ++i)
		{
			if (allFootballers[i].IsBiggerThanComparedBy(allFootballers[i + 1], method))
			{
				ChangeTwoPlayers(i);
				int j = i - 1;
				while (j >= 0)
				{
					if (allFootballers[j].IsBiggerThanComparedBy(allFootballers[j + 1], method))
					{
						ChangeTwoPlayers(j);
					}
					--j;
				}
			}
			else
			{
				continue;
			}
		}
	}
	else
	{
		for (unsigned i = 0; i < used - 1; ++i)
		{
			if (not allFootballers[i].IsBiggerThanComparedBy(allFootballers[i + 1], method))
			{
				ChangeTwoPlayers(i);
				int j = i - 1;
				while (j >= 0)
				{
					if (not allFootballers[j].IsBiggerThanComparedBy(allFootballers[j + 1], method))
					{
						ChangeTwoPlayers(j);
					}
					--j;
				}
			}
			else
			{
				continue;
			}
		}
	}
}

unsigned Club::FindSumOf(unsigned(Footballer::* method)() const) const
{
	unsigned sum = 0;
	for (unsigned i = 0; i < used; ++i)
	{
		sum += (allFootballers[i].*method)();
	}
	return sum;
}

double Club::FindSumOf(double(Footballer::* method)() const) const
{
	double sum = 0;
	for (unsigned i = 0; i < used; ++i)
	{
		sum += (allFootballers[i].*method)();
	}
	return sum;
}

void Club::ChangeCoefficient(double newCoef, bool setNewCoefForAll)
{
	if (newCoef <= 0)
	{
		throw("Club::ChangeCoefficient::zero or negative coefficient");
	}
	else
	{
		coefficient = newCoef;
	}
	if (setNewCoefForAll)
	{
		for (unsigned i = 0; i < used; ++i)
		{
			allFootballers[i].ChangeCoefficient(newCoef);
		}
	}
}

void Club::ReadFrom(std::istream& is)
{
	is >> clubName
		>> coefficient
		>> size
		>> used;
	allFootballers = new Footballer[size];
	for (unsigned i = 0; i < used; ++i)
	{
		is >> allFootballers[i];
		allFootballers[i].ChangeCoefficient(coefficient);
	}
}
Club** ReadMultipleClubsFromFile(const Club::DataAboutClub* dataAboutClubs, unsigned length, std::istream& is)
{
	Club** result = new Club * [length];
	for (unsigned i = 0; i < length; ++i)
	{
		result[i] = new Club(dataAboutClubs[i].DA_clubName, dataAboutClubs[i].DA_size, dataAboutClubs[i].DA_coefficient);
	}
	std::string clubName;
	while (is >> clubName)
	{
		// bad idea 
		// hash table - ?
		for (unsigned i = 0; i < length; ++i)
		{
			if (clubName == result[i]->clubName)
			{
				Footballer temp;
				is >> temp;
				result[i]->AddFootballer(temp);
			}
		}
	}
	return result;
}
std::istream& operator>>(std::istream& is, Club& C)
{
	C.ReadFrom(is);
	return is;
}
std::ostream& operator<<(std::ostream& os, const Club& C)
{
	C.WriteTo(os);
	return os;
}
std::istream& operator>>(std::istream& is, Club::DataAboutClub& DA)
{
	is >> DA.DA_clubName
		>> DA.DA_coefficient
		>> DA.DA_size;
	return is;
}

Club& MaxClub(unsigned(Footballer::* method)() const, Club** clubs, unsigned length)
{
	unsigned maxIndex = 0;
	for (unsigned i = 1; i < length; ++i)
	{
		if (clubs[i]->FindSumOf(method) > clubs[maxIndex]->FindSumOf(method))
		{
			maxIndex = i;
		}
	}
	return *clubs[maxIndex];
}

Club& MaxClub(double(Footballer::* method)() const, Club** clubs, unsigned length)
{
	unsigned maxIndex = 0;
	for (unsigned i = 1; i < length; ++i)
	{
		if (clubs[i]->FindSumOf(method) > clubs[maxIndex]->FindSumOf(method))
		{
			maxIndex = i;
		}
	}
	return *clubs[maxIndex];
}
