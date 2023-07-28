#pragma once
#include "Find.h"

class DotaPicker :public Find
{
public:
	DotaPicker();

	void GetProposedHeroes(int side);

	void DeleteSelectedHero();
	std::string RemoveBannedHero();

	void ProposedHeroesRadiant(int side);
	void ProposedHeroesDire(int side);

	void WinProbability(int sideChoice, int pickIndex);
	double GetAllWinProbabilityPoints() { return winProbabilityRadiant + winProbabilityDire; }

	int GetRadiantPercent() { return (winProbabilityRadiant * 100) / GetAllWinProbabilityPoints(); }
	int GetDirePercent() { return 100 - GetRadiantPercent(); }

	std::string PrintProposedHeroes(int side);

private:
	bool choiceW = true;
	bool isHeroSelected = false;
	bool isAlready = false;

	std::vector<std::pair<std::string, double>> proposedHeroesRadiant;
	std::vector<std::pair<std::string, double>> proposedHeroesDire;

	double winProbabilityRadiant = 0;
	double winProbabilityDire = 0;
	int allWinProbabilityPoints = 0;
	

	int radiantPercent = 0;
	int direPersent = 0;
};

