#include <iostream>
#include "Footballer.h"
#include <fstream>
#include "Club.h"

int main()
{
	{
		std::cout << "---General checkout---" << std::endl;

		std::cout << "class Footballer" << std::endl;
		Footballer Ronaldo{ "Cristiano", "Ronaldo", 23 };
		Footballer Shevchenko{ "Shevchenko", "Andrii", 15 };
		std::cout << Ronaldo
			<< Shevchenko
			<< std::boolalpha
			<< Ronaldo.IsBiggerThanComparedBy(Shevchenko, &Footballer::GetScoredGoals)
			<< std::endl;

		std::cout << "class Club" << std::endl;
		Club Barcelona{ "Barcelona", 2, 2000 };
		Barcelona.AddFootballer(Ronaldo);
		Barcelona.AddFootballer(Shevchenko);
		std::cout << Barcelona;
		Club BarcelonaCopy{ Barcelona };
		BarcelonaCopy.ChangeCoefficient(2, true);
		std::cout << Barcelona
			<< BarcelonaCopy
			<< Ronaldo;

		std::cout << "---End of the section---" << std::endl;
		system("pause");
		system("CLS");
	}

	{
		std::cout << "---Reading from file, sorting footballers and counting sum---" << std::endl;
		std::ifstream fin;
		fin.open("text.txt");
		Club Barcelona;
		if (fin.good())
		{
			Barcelona.ReadFrom(fin);
			std::cout << Barcelona;
		}
		else
		{
			throw("Unknown error");
		}
		fin.close();
		std::cout << "Sorted Barcelona by player salary" << std::endl;
		Barcelona.SortFootballersBy(&Footballer::GetSalary, true);
		std::cout << Barcelona;
		std::cout << "Club total goals: " << Barcelona.FindSumOf(&Footballer::GetScoredGoals) << std::endl;
		std::cout << "Club total salaries: " << Barcelona.FindSumOf(&Footballer::GetSalary) << std::endl;
		std::cout << "---End of the section---" << std::endl;
		system("pause");
		system("CLS");
	}

	{
		std::cout << "---Read multiple clubs from file---" << std::endl;
		std::ifstream fin("three_clubs.txt");
		Club::DataAboutClub* DA;
		Club** allClubs;
		unsigned DA_size;
		unsigned allClubsSize;
		if (fin.good())
		{
			fin >> DA_size;
			allClubsSize = DA_size;
			DA = new Club::DataAboutClub[DA_size];
			for (unsigned i = 0; i < DA_size; ++i)
			{
				fin >> DA[i];
			}
			allClubs = ReadMultipleClubsFromFile(DA, DA_size, fin);
		}
		else
		{
			throw("Unknown error");
		}
		fin.close();

		for (unsigned i = 0; i < allClubsSize; ++i)
		{
			allClubs[i]->SortFootballersBy(&Footballer::GetScoredGoals, true);
			std::cout << *allClubs[i];
			std::cout << "Club total goals: " << allClubs[i]->FindSumOf(&Footballer::GetScoredGoals) << std::endl;
			std::cout << "Club total salaries: " << allClubs[i]->FindSumOf(&Footballer::GetSalary) << std::endl;
		}

		std::cout << "Club with the most goals: " << MaxClub(&Footballer::GetScoredGoals, allClubs, allClubsSize).GetClubName() << std::endl;
		std::cout << "Club with the highest salary budget: " << MaxClub(&Footballer::GetSalary, allClubs, allClubsSize).GetClubName() << std::endl;
		std::cout << "---End of the section---" << std::endl;
		system("pause");
		system("CLS");
	}
	return 0;
}