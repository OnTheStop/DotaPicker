#include "Find.h"

Find::Find()
{
}

size_t Find::GetResponseToString(void* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);

	return size * nmemb;
}

void Find::GetHTML(int sideChoice)
{
	CURL* curl;
	CURLcode response;
	std::string URL = "https://www.dota2protracker.com/hero/" + GetHeroToFind() + "#";
	std::cout << URL;
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, GetResponseToString);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &heroHtmlCode);
	response = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
}

void Find::WordSearch(int choiceSide, const std::string& selectedHero)
{
	int i = 0;
	int sideChoice = choiceSide;
	int index = 1;
	std::string tempNameHero;
	std::string tempFirstWord;
	std::string tempSecondWord;
	
	tempNameHero = selectedHero;

	if (tempNameHero == "Keeper of the Light")
	{
		heroToFind = "Keeper%20of%20the%20Light";
		return;
	}
	if (tempNameHero == "Queen of Pain")
	{
		heroToFind = "Queen%20of%20Pain";
		return;
	}

	while (i < tempNameHero.size())
	{
		if (islower(tempNameHero[0]))
			tempNameHero[0] = toupper(tempNameHero[0]);

		if (tempNameHero[i] == ' ')
		{
			tempNameHero[i + 1] = toupper(tempNameHero[i + 1]);
			index = 2;
		}
		if (tempNameHero[i] == '-')
		{
			tempNameHero[i + 1] = toupper(tempNameHero[i + 1]);
			index = 3;
		}

		if (index == 1)
			tempFirstWord += tempNameHero[i];
		else
			tempSecondWord += tempNameHero[i + 1];


		i++;
	}
	//добавить поиск по первым буквам

	if (sideChoice == 1)
	{
		radiantCount++;

		if (radiantCount == 1)
			radiantHero1 = tempNameHero;
		else if (radiantCount == 2)
			radiantHero2 = tempNameHero;
		else if (radiantCount == 3)
			radiantHero3 = tempNameHero;
		else if (radiantCount == 4)
			radiantHero4 = tempNameHero;
		else if (radiantCount == 5)
			radiantHero5 = tempNameHero;
	}
	else
	{
		direCount++;

		if (direCount == 1)
			direHero1 = tempNameHero;
		else if (direCount == 2)
			direHero2 = tempNameHero;
		else if (direCount == 3)
			direHero3 = tempNameHero;
		else if (direCount == 4)
			direHero4 = tempNameHero;
		else if (direCount == 5)
			direHero5 = tempNameHero;
	}
	
	if (index == 1) {
		heroToFind = tempNameHero;
		heroToDelete = tempNameHero;
	}
	if (index == 2)
	{
		heroToFind = tempFirstWord + "%20" + tempSecondWord;
		heroToDelete = tempFirstWord + " " + tempSecondWord;
		heroToDelete.erase(heroToDelete.begin() + heroToDelete.size() - 1);
	}
	if (index == 3)
	{
		heroToFind = tempFirstWord + "-" + tempSecondWord;
		heroToDelete = tempFirstWord + "-" + tempSecondWord;
		heroToDelete.erase(heroToDelete.begin() + heroToDelete.size() - 1);
	}
}

double Find::heroSearchWR()
{
	std::string temp = "Matches last 8 days";
	std::string valueWR;
	double tempHeroWR = 0;
	const char* arr = heroHtmlCode.c_str();
	int i = 0;

	while (arr)
	{
		if (arr[i] == 'M')
		{
			int j = 0;

			while (!temp.empty())
			{
				if (j == temp.size() - 1)
				{
					while (arr[i] != '>')
						i++;

					i++;

					while (arr[i] != '%')
					{
						valueWR += arr[i];
						i++;
					}

				
					return tempHeroWR = stod(valueWR);
				}

				if (arr[i] != temp[j])
					break;

				i++; j++;
			}
		}
		i++;
	};

	delete[] arr;
	return tempHeroWR;
}

void Find::SearchStatsHeroes()
{
	pick.clear();

	CoupleHeroes tempHero;
	std::string tr = "<tr>";
	std::string title = "title=\"";
	std::string data_order = "data-order\"";
	bool isData_order = true;
	bool isValueGames = true;
	bool isReady = false;
	bool isAlready = false;
	bool isExit = false;

	std::string heroName;
	std::string heroWr_str;
	std::string winGames_str;
	std::string loseGames_str;
	char check;

	const char* arr = heroHtmlCode.c_str();
	int trCounter = 0;
	int data_orderCounter = 0;
	int i = 0;
	
	while (arr)
	{
		isReady = false;
		check = arr[i];

		if (arr[i] == '<')
		{
			int j = 0;
			
			while (!tr.empty())
			{


				if (j == tr.size() - 1)
				{
					trCounter++;

					if (trCounter == 1)
						break;

					while (isReady != true)
					{
						check = arr[i];

						if (arr[i] == 't')
						{
							int y = 0;

							while (!title.empty())
							{
								check = arr[i];

								if (y == title.size())
								{
									heroName.clear();

									while (arr[i] != '\"')
									{
										heroName += arr[i];
										i++;
									}

									tempHero.SetHeroName(heroName);
								}
								
								if (arr[i] != title[y])
									break;

								i++; y++;
							}
						}


						if (arr[i] == '(' && arr[i - 1] != 'd' && isValueGames == true || arr[i] == '0' && arr[i - 1] == ' ' && arr[i + 1] == '\n' && isValueGames == true)
						{
							i++;
							winGames_str.erase();
							loseGames_str.erase();

							if (arr[i - 1] == '(')
							{
								while (arr[i] != '-')
								{
									winGames_str += arr[i];
									i++;
								}
								i++;

								while (arr[i] != ')')
								{
									loseGames_str += arr[i];
									i++;
								}

								tempHero.SetWinGamesW(stoi(winGames_str));
								tempHero.SetLoseGamesW(stoi(loseGames_str));
								tempHero.SetAllGamesW(stoi(winGames_str), stoi(loseGames_str));
								tempHero.SetHeroWrWith();
							}
							
							isValueGames = false;
						}

						if (arr[i] == '(' && arr[i - 1] != 'd' && isValueGames == false || arr[i] == '0' && arr[i - 1] == '>' && arr[i + 1] == '<' && isValueGames == false)
						{
							i++;
							winGames_str.erase();
							loseGames_str.erase();

							check = arr[i];

							if (arr[i - 1] == '(' || arr[i + 1] != '/')
							{
								while (arr[i] != '-')
								{
									winGames_str += arr[i];
									i++;
								}
								i++;

								while (arr[i] != ')')
								{
									loseGames_str += arr[i];
									i++;
								}

								tempHero.SetWinGamesA(stoi(winGames_str));
								tempHero.SetLoseGamesA(stoi(loseGames_str));
								tempHero.SetAllGamesA(stoi(winGames_str), stoi(loseGames_str));
								tempHero.SetHeroWrAgainst();
							}
							
							tempHero.SetValueCoeffHeroW();
							tempHero.SetValueCoeffHeroA();
							tempHero.SetValueCoeffAnotherHeroA();

							pick.push_back(tempHero);
							tempHero.Clear();

							if (data_orderCounter == 369)
								return;

							isValueGames = true;
							isReady = true;
						}

						i++;
					}
				}
				
				if (arr[i] != tr[j])
					break;


				i++; j++;
			}

		}

		if (arr[i] == 't' && arr[i - 1] == '/' && arr[i + 1] == 'b')
		{
			int e = 0;

			while (arr[i] != '>')
			{
				check = arr[i];
				i++; e++;
			}
			if (e == 5)
				return;
		}

		i++;
	}
}

void Find::CheckOfStats(int pickIndex, int sideChoice)
{
	if (pickIndex == 2 && sideChoice == 1)
	{
		if (radiantHeroWR1 != 0)
		{
			
		}
	}
}

void Find::ClearHtmlCode() { heroHtmlCode.clear(); };

void Find::SetHeroWR(int indexSide, bool sideChoice)
{
	if (sideChoice == true)
	{
		if (indexSide == 1)
			radiantHeroWR1 = heroSearchWR();
		else if (indexSide == 2)
			radiantHeroWR2 = heroSearchWR();
		else if (indexSide == 3)
			radiantHeroWR3 = heroSearchWR();
		else if (indexSide == 4)
			radiantHeroWR4 = heroSearchWR();
		else if (indexSide == 5)
			radiantHeroWR5 = heroSearchWR();
	}
	else
	{
		if (indexSide == 1)
			direHeroWR1 = heroSearchWR();
		else if (indexSide == 2)
			direHeroWR2 = heroSearchWR();
		else if (indexSide == 3)
			direHeroWR3 = heroSearchWR();
		else if (indexSide == 4)
			direHeroWR4 = heroSearchWR();
		else if (indexSide == 5)
			direHeroWR5 = heroSearchWR();
	}
}

std::string Find::GetHeroToFind() 
{
	return this->heroToFind;
}
std::string Find::GetHeroHtmlCode() 
{
	return std::string(heroHtmlCode);
}

void Find::SortVec()
{
	sort(pick.begin(), pick.end(), [](CoupleHeroes &ch1,CoupleHeroes &ch2) {

		return  ch1.GetValueCoeffAnotherHeroA() < ch2.GetValueCoeffAnotherHeroA();
		});
}

void Find::SortVecW()
{
	sort(pick.begin(), pick.end(), [](CoupleHeroes& ch1, CoupleHeroes& ch2) {

		return  ch1.GetValueCoeffHeroW() > ch2.GetValueCoeffHeroW();
		});
}

void Find::SortVecAnotherA()
{
	sort(pick.begin(), pick.end(), [](CoupleHeroes& ch1, CoupleHeroes& ch2) {

		return  ch1.GetValueCoeffAnotherHeroA() > ch2.GetValueCoeffAnotherHeroA();
		});
}


void Find::Printf()
{
	SortVec();

	for (auto& el : this->pick)
	{
		std::cout << std::endl << heroToFind << " & " << el.GetHeroName() << "\t\twith: " << std::setprecision(3) << el.GetHeroWrWith() << "% (" << el.GetWinGamesW() << "-" << el.GetLoseGamesW() << ")";
		std::cout << "\tcoeffW: " << el.GetValueCoeffHeroW();
		std::cout << "\tagainst: " << std::setprecision(3) << el.GetHeroWrAgainst() << "% (" << el.GetWinGamesA() << "-" << el.GetLoseGamesA() << ")" << "\tcoeffA: ";
		std::cout << el.GetValueCoeffHeroA() << "\tcoeffAA: " << el.GetValueCoeffAnotherHeroA() << std::endl;
	}

	pick.clear();
}

CoupleHeroes::CoupleHeroes()
{
}

void CoupleHeroes::SetValueCoeffHeroW()
{
	double coeff = 0;

	if (this->allGamesW >= 1 && this->allGamesW <= 10)
		coeff = 0.3;
	else if (this->allGamesW >= 10 && this->allGamesW <= 30)
		coeff = 0.6;
	else if (this->allGamesW >= 30 && this->allGamesW <= 50)
		coeff = 0.8;
	else if (this->allGamesW >= 50 && this->allGamesW < 100)
		coeff = 0.9;
	else if (this->allGamesW == 100)
		coeff = 1;
	else if (this->allGamesW > 100 && this->allGamesW <= 300)
		coeff = 1.05;
	else if (this->allGamesW >= 300 && this->allGamesW <= 500)
		coeff = 1.075;
	else if (this->allGamesW >= 500 && this->allGamesW <= 1000)
		coeff = 1.1;
	else if (this->allGamesW > 1000)
		coeff = 1.115;
	
	this->valueCoeffHeroW = coeff * this->heroWrWith;
}

void CoupleHeroes::SetValueCoeffHeroA()
{
	double coeff = 0;

	if (this->allGamesA >= 1 && this->allGamesA <= 10)
		coeff = 0.3;
	else if (this->allGamesA >= 10 && this->allGamesA <= 30)
		coeff = 0.6;
	else if (this->allGamesA >= 30 && this->allGamesA <= 50)
		coeff = 0.8;
	else if (this->allGamesA >= 50 && this->allGamesA < 100)
		coeff = 0.9;
	else if (this->allGamesA == 100)
		coeff = 1;
	else if (this->allGamesA > 100 && this->allGamesA <= 300)
		coeff = 1.05;
	else if (this->allGamesA >= 300 && this->allGamesA <= 500)
		coeff = 1.075;
	else if (this->allGamesA >= 500 && this->allGamesA <= 1000)
		coeff = 1.1;
	else if (this->allGamesA > 1000)
		coeff = 1.115;

	this->valueCoeffHeroA = coeff * this->heroWrAgainst;
}

void CoupleHeroes::SetValueCoeffAnotherHeroA()
{
	double coeff = 0;
	int anotherHeroWr = (100 - this->heroWrAgainst);

	if (this->allGamesA >= 1 && this->allGamesA <= 10)
		coeff = 0.3;
	else if (this->allGamesA >= 10 && this->allGamesA <= 30)
		coeff = 0.6;
	else if (this->allGamesA >= 30 && this->allGamesA <= 50)
		coeff = 0.8;
	else if (this->allGamesA >= 50 && this->allGamesA < 100)
		coeff = 0.9;
	else if (this->allGamesA == 100)
		coeff = 1;
	else if (this->allGamesA > 100 && this->allGamesA <= 300)
		coeff = 1.05;
	else if (this->allGamesA >= 300 && this->allGamesA <= 500)
		coeff = 1.075;
	else if (this->allGamesA >= 500 && this->allGamesA <= 1000)
		coeff = 1.1;
	else if (this->allGamesA > 1000)
		coeff = 1.115;

	this->valueCoeffAnotherHeroA = coeff * anotherHeroWr;
}

void CoupleHeroes::Clear()
{
	heroName.clear();
	heroWrWith = 0;
	heroWrAgainst = 0;
	winGamesW = 0;
	loseGamesW = 0;
	allGamesW = 0;
	winGamesA = 0;
	loseGamesA = 0;
	allGamesA = 0;
}

