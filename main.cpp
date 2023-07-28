#include <iostream>
#include <Windows.h>

#include "Find.h"
#include "DotaPicker.h"

using namespace std;

int main()
{
	string tempH;
	int pickIndex = 1;
	int radiantPickIndex = 1;
	int direPickIndex = 1;
	bool radiantSide = true;
	int sideChoice = 0;
	DotaPicker pick;
	string selectedHero;

	while (pickIndex < 11)
	{
		cout << "Radiant(1) or Dire(2)?" << endl << "Choice: ";
		cin >> sideChoice;

		if (sideChoice == 1)
		{
			radiantSide = true;
			selectedHero = pick.PrintProposedHeroes(sideChoice);
			pick.WordSearch(sideChoice, selectedHero);
			pick.GetHTML(sideChoice);
			pick.SetHeroWR(radiantPickIndex, radiantSide);
			pick.SearchStatsHeroes();	
			pick.GetProposedHeroes(sideChoice);
			pick.WinProbability(sideChoice, pickIndex);	
			pick.ClearHtmlCode();
			//pick.Printf();
			radiantPickIndex++;
		}
		if (sideChoice == 2)
		{
			radiantSide = false;
			selectedHero = pick.PrintProposedHeroes(sideChoice);
			pick.WordSearch(sideChoice, selectedHero);
			pick.GetHTML(sideChoice);
			pick.SetHeroWR(direPickIndex, radiantSide);
			pick.SearchStatsHeroes();
			pick.GetProposedHeroes(sideChoice);
			pick.WinProbability(sideChoice, pickIndex);
			pick.ClearHtmlCode();

			direPickIndex++;
		}
		pickIndex++;
	}

	cout << "\nRadiant: " << pick.GetRadiantPercent() << " : " << pick.GetDirePercent() << " :Dire" << endl;

	system("pause");
}