#pragma once
#define CURL_STATICLIB

#include <Windows.h>
#include <curl/curl.h>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>


class CoupleHeroes
{
public:
	CoupleHeroes();

	void SetHeroName(std::string heroName) { this->heroName = heroName; }
	void SetHeroWrWith() { this->heroWrWith = (float)(this->winGamesW * 100) / (float)allGamesW; }
	void SetHeroWrAgainst() { this->heroWrAgainst = (float)(this->winGamesA * 100) / (float)allGamesA; }

	void SetWinGamesW(int winGamesW) { this->winGamesW = winGamesW; }
	void SetLoseGamesW(int loseGamesW) { this->loseGamesW = loseGamesW; }
	void SetAllGamesW(int winGamesW, int loseGamesW) { this->allGamesW = winGamesW + loseGamesW; }

	void SetWinGamesA(int winGamesA) { this->winGamesA = winGamesA; }
	void SetLoseGamesA(int loseGamesA) { this->loseGamesA = loseGamesA; }
	void SetAllGamesA(int winGamesA, int loseGamesA) { this->allGamesA = winGamesA + loseGamesA; }

	void SetValueCoeffHeroW();
	void SetValueCoeffHeroA();
	void SetValueCoeffAnotherHeroA();

	void Clear();

	std::string GetHeroName() { return this->heroName; }
	float GetHeroWrWith() { return this->heroWrWith; }
	float GetHeroWrAgainst() { return this->heroWrAgainst; }
	int GetWinGamesW() { return this->winGamesW; }
	int GetLoseGamesW() { return this->loseGamesW; }
	int GetWinGamesA() { return this->winGamesA; }
	int GetLoseGamesA() { return this->loseGamesA; }

	double GetValueCoeffHeroW() { return this->valueCoeffHeroW; }
	double GetValueCoeffHeroA() { return this->valueCoeffHeroA; }
	double GetValueCoeffAnotherHeroA() { return this->valueCoeffAnotherHeroA; }
	
protected:
	std::string heroName;
	float heroWrWith = 0;
	float heroWrAgainst = 0;
	int winGamesW = 0;
	int loseGamesW = 0;
	int allGamesW = 0;
	int winGamesA = 0;
	int loseGamesA = 0;
	int allGamesA = 0;

	double valueCoeffHeroW = 0;
	double  valueCoeffHeroA = 0;
	double valueCoeffAnotherHeroA = 0;
};

class Find : public CoupleHeroes {
public:
	Find();

	static size_t GetResponseToString(void* contents, size_t size, size_t nmemb, void* userp);
	void GetHTML(int sideChoice);

	void WordSearch(int sideChoice, const std::string& selectedHero); // поиск по слову
	double heroSearchWR(); // поиск винрейта героя из строки

	void SearchStatsHeroes();
	void CheckOfStats(int pickIndex, int sideChoice);
	void ClearHtmlCode();

	void SetHeroWR(int indexSide, bool sideChoice);

	std::string GetRadiantHero1()  { return radiantHero1; }
	std::string GetRadiantHero2()  { return radiantHero2; }
	std::string GetRadiantHero3()  { return radiantHero3; }
	std::string GetRadiantHero4()  { return radiantHero4; }
	std::string GetRadiantHero5()  { return radiantHero5; }

	std::string GetDireHero1()  { return direHero1; }
	std::string GetDireHero2()  { return direHero2; }
	std::string GetDireHero3()  { return direHero3; }
	std::string GetDireHero4()  { return direHero4; }
	std::string GetDireHero5()  { return direHero5; }

	double GetRadiantHeroWR1()  { return radiantHeroWR1; }
	double GetRadiantHeroWR2()  { return radiantHeroWR2; }
	double GetRadiantHeroWR3()  { return radiantHeroWR3; }
	double GetRadiantHeroWR4()  { return radiantHeroWR4; }
	double GetRadiantHeroWR5()  { return radiantHeroWR5; }

	double GetDireHeroWR1()  { return direHeroWR1; }
	double GetDireHeroWR2()  { return direHeroWR2; }
	double GetDireHeroWR3()  { return direHeroWR3; }
	double GetDireHeroWR4()  { return direHeroWR4; }
	double GetDireHeroWR5()  { return direHeroWR5; }

	std::string GetHeroToFind() ;
	std::string GetHeroToDelete()  { return heroToDelete; }
	std::string GetHeroHtmlCode() ;
	void SortVec();
	void SortVecW();
	void SortVecAnotherA();

	void Printf();

	std::vector<CoupleHeroes>& GetVecPick() { return pick; }

private:
	int radiantCount = 0;
	int direCount = 0;

	std::string radiantHero1, radiantHero2, radiantHero3, radiantHero4, radiantHero5;
	std::string direHero1, direHero2, direHero3, direHero4, direHero5;

	double radiantHeroWR1 = 0;
	double radiantHeroWR2 = 0;
	double radiantHeroWR3 = 0;
	double radiantHeroWR4 = 0;
	double radiantHeroWR5 = 0;
	double direHeroWR1 = 0;
	double direHeroWR2 = 0;
	double direHeroWR3 = 0;
	double direHeroWR4 = 0;
	double direHeroWR5 = 0;

	std::string heroToFind;
	std::string heroToDelete;
	std::string heroHtmlCode;

	std::vector<CoupleHeroes> pick;
};


