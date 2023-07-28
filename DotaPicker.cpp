#include "DotaPicker.h"

using namespace std;

DotaPicker::DotaPicker() {}

void DotaPicker::GetProposedHeroes(int side)
{
	DeleteSelectedHero();

	if (side == 1)
	{
		ProposedHeroesRadiant(side);
		ProposedHeroesDire(side);
	}

	if (side == 2)
	{
		ProposedHeroesRadiant(side);
		ProposedHeroesDire(side);
	}
}

void DotaPicker::DeleteSelectedHero()
{
	proposedHeroesRadiant.erase(std::remove_if(proposedHeroesRadiant.begin(), proposedHeroesRadiant.end(), [&](const auto& ve) {
		return ve.first == GetHeroToDelete();
		}), proposedHeroesRadiant.end());

	proposedHeroesDire.erase(std::remove_if(proposedHeroesDire.begin(), proposedHeroesDire.end(), [&](const auto& ve) {
		return ve.first == GetHeroToDelete();
		}), proposedHeroesDire.end());

}

std::string DotaPicker::RemoveBannedHero()
{
	std::string tempNameHero;
	isHeroSelected = false;

	while (true)
	{

		std::cout << "Enter the name of the Hero: ";
		while (tempNameHero.empty())
			getline(std::cin >> std::ws, tempNameHero);


		if (tempNameHero == "1" || tempNameHero == "2" || tempNameHero == "3" || tempNameHero == "4" || tempNameHero == "5" || tempNameHero == "6")
		{
			int temp = stoi(tempNameHero);
			proposedHeroesRadiant.erase(remove(proposedHeroesRadiant.begin(), proposedHeroesRadiant.end(), proposedHeroesRadiant[temp - 1]), proposedHeroesRadiant.end());
			proposedHeroesDire.erase(remove(proposedHeroesDire.begin(), proposedHeroesDire.end(), proposedHeroesDire[temp - 1]), proposedHeroesDire.end());

			return tempNameHero;
		}
		else
			break;
	}

	isHeroSelected = true;
	return tempNameHero;
}

void DotaPicker::ProposedHeroesRadiant(int side)
{
	if (side == 1)
	{
		if (proposedHeroesRadiant.empty())
		{
			for (auto& el : GetVecPick())
			{
				proposedHeroesRadiant.push_back(std::make_pair(el.GetHeroName(), el.GetValueCoeffHeroW()));
			}
		}
		else
		{
			for (auto& el : proposedHeroesRadiant)
			{
				for (auto& ele : GetVecPick())
				{
					if (el.first == ele.GetHeroName()) {
						el.second += ele.GetValueCoeffHeroW();
						break;
					}
				}
			}
		}
	}
	else
	{
		if (proposedHeroesRadiant.empty())
		{
			for (auto& el : GetVecPick())
			{
				proposedHeroesRadiant.push_back(std::make_pair(el.GetHeroName(), el.GetValueCoeffAnotherHeroA()));
			}
		}
		else
		{
			for (auto& el : proposedHeroesRadiant)
			{
				for (auto& ele : GetVecPick())
				{
					if (el.first == ele.GetHeroName()) {
						el.second += ele.GetValueCoeffAnotherHeroA();
						break;
					}
				}
			}
		}
	}
}

void DotaPicker::ProposedHeroesDire(int side)
{
	if (side == 1)
	{
		if (proposedHeroesDire.empty())
		{
			for (auto& el : GetVecPick())
			{
				proposedHeroesDire.push_back(make_pair(el.GetHeroName(), el.GetValueCoeffAnotherHeroA()));
			}
		}
		else
		{
			for (auto& el : proposedHeroesDire)
			{
				for (auto& ele : GetVecPick())
				{
					if (el.first == ele.GetHeroName()) {
						el.second += ele.GetValueCoeffAnotherHeroA();
						break;
					}
				}
			}
		}
	}
	else
	{
		if (proposedHeroesDire.empty())
		{
			for (auto& el : GetVecPick())
			{
				proposedHeroesDire.push_back(make_pair(el.GetHeroName(), el.GetValueCoeffHeroW()));
			}
		}
		else
		{
			for (auto& el : proposedHeroesDire)
			{
				for (auto& ele : GetVecPick())
				{
					if (el.first == ele.GetHeroName()) {
						el.second += ele.GetValueCoeffHeroW();
						break;
					}
				}
			}
		}
	}
}

void DotaPicker::WinProbability(int sideChoice, int pickIndex)
{
	if (pickIndex == 1)
		return;

	if (GetDireHero1() != "" && GetRadiantHero2() == "" && isAlready == false)
	{
		for (auto& el : GetVecPick())
		{
			if (el.GetHeroName() == GetDireHero1())
				winProbabilityDire += el.GetValueCoeffAnotherHeroA();
		}
	}
	if (GetRadiantHero1() != "" && GetDireHero2() == "" && isAlready == false)
	{
		for (auto& el : GetVecPick())
		{
			if (el.GetHeroName() == GetRadiantHero1())
				winProbabilityRadiant += el.GetValueCoeffAnotherHeroA();
		}
		isAlready = true;
	}

	if (sideChoice == 1)
	{
		for (auto& el : GetVecPick())
		{
			if (el.GetHeroName() == GetRadiantHero1() && GetRadiantHero1() != "")
				winProbabilityRadiant += el.GetValueCoeffHeroW();
			if (el.GetHeroName() == GetRadiantHero2() && GetRadiantHero2() != "")
				winProbabilityRadiant += el.GetValueCoeffHeroW();
			if (el.GetHeroName() == GetRadiantHero3() && GetRadiantHero3() != "")
				winProbabilityRadiant += el.GetValueCoeffHeroW();
			if (el.GetHeroName() == GetRadiantHero4() && GetRadiantHero4() != "")
				winProbabilityRadiant += el.GetValueCoeffHeroW();
			if (el.GetHeroName() == GetRadiantHero5() && GetRadiantHero5() != "")
				winProbabilityRadiant += el.GetValueCoeffHeroW();

			if (el.GetHeroName() == GetDireHero1() && GetDireHero1() != "")
				winProbabilityRadiant += el.GetValueCoeffHeroA();
			if (el.GetHeroName() == GetDireHero2() && GetDireHero2() != "")
				winProbabilityRadiant += el.GetValueCoeffHeroA();
			if (el.GetHeroName() == GetDireHero3() && GetDireHero3() != "")
				winProbabilityRadiant += el.GetValueCoeffHeroA();
			if (el.GetHeroName() == GetDireHero4() && GetDireHero4() != "")
				winProbabilityRadiant += el.GetValueCoeffHeroA();
			if (el.GetHeroName() == GetDireHero5() && GetDireHero5() != "")
				winProbabilityRadiant += el.GetValueCoeffHeroA();

			if (pickIndex == 10 && el.GetHeroName() == GetDireHero5())
				winProbabilityDire += el.GetValueCoeffAnotherHeroA();
		}
	}
	else
	{
		for (auto& el : GetVecPick())
		{
			if (el.GetHeroName() == GetDireHero1() && GetDireHero1() != "")
				winProbabilityDire += el.GetValueCoeffHeroW();
			if (el.GetHeroName() == GetDireHero2() && GetDireHero2() != "")
				winProbabilityDire += el.GetValueCoeffHeroW();
			if (el.GetHeroName() == GetDireHero3() && GetDireHero3() != "")
				winProbabilityDire += el.GetValueCoeffHeroW();
			if (el.GetHeroName() == GetDireHero4() && GetDireHero4() != "")
				winProbabilityDire += el.GetValueCoeffHeroW();
			if (el.GetHeroName() == GetDireHero5() && GetDireHero5() != "")
				winProbabilityDire += el.GetValueCoeffHeroW();

			if (el.GetHeroName() == GetRadiantHero1() && GetRadiantHero1() != "")
				winProbabilityDire += el.GetValueCoeffHeroA();
			if (el.GetHeroName() == GetRadiantHero2() && GetRadiantHero2() != "")
				winProbabilityDire += el.GetValueCoeffHeroA();
			if (el.GetHeroName() == GetRadiantHero3() && GetRadiantHero3() != "")
				winProbabilityDire += el.GetValueCoeffHeroA();
			if (el.GetHeroName() == GetRadiantHero4() && GetRadiantHero4() != "")
				winProbabilityDire += el.GetValueCoeffHeroA();
			if (el.GetHeroName() == GetRadiantHero5() && GetRadiantHero5() != "")
				winProbabilityDire += el.GetValueCoeffHeroA();

			if (pickIndex == 10 && el.GetHeroName() == GetRadiantHero5())
				winProbabilityRadiant += el.GetValueCoeffAnotherHeroA();
		}
	}
 }


string DotaPicker::PrintProposedHeroes(int side)
{
	int i = 1;
	string selectedHero;
	isHeroSelected = false;

	if (side == 1)
	{
		sort(proposedHeroesRadiant.begin(), proposedHeroesRadiant.end(), [](const auto& ve1, auto& ve2) {
			return ve1.second > ve2.second;
			});


		while (isHeroSelected != true)
		{
			i = 1;

		for (auto &el : proposedHeroesRadiant)
		{
			cout << i << "." << el.first << "\t" << el.second << "\tChoose " << i << " to ban!" << endl;
			i++;

			if (i == 7)
				break;
		}

		selectedHero = RemoveBannedHero();
		}
	}
	else
	{
		sort(proposedHeroesDire.begin(), proposedHeroesDire.end(), [](const auto& ve1, auto& ve2) {
			return ve1.second > ve2.second;
			});


		while (isHeroSelected != true)
		{
			i = 1;

			for (auto& el : proposedHeroesDire)
			{
				cout << i << "." << el.first << "\t" << el.second << "\tChoose " << i << " to ban!" << endl;
				i++;

				if (i == 7)
					break;
			}

			selectedHero = RemoveBannedHero();
		}
	}

	return selectedHero;
}



