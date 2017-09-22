#pragma once
#pragma once
#include <map>
#include <string>
#include "stdafx.h"
//TODO:add header guards

using namespace std;
typedef std::map<std::string, int> Dictionary;
typedef struct formationSpot {
	int x;
	int y;
} formationSpot;

class Minion {

private:
	bool death;
	// defined as int, try to stick to round numbers
	Dictionary charStats;
	int currentHP;
	int maxHP;
	int strength;
	int dex;
	//watch out, because C++ doesn't support decimal type, 
	//weight measured in cm and weight measured in cg
	int height;
	int weight;
	int discipline;
	int stamina;
	bool ranged;
	int armour;
	int speed;
	//formation info
	formationSpot formationPlace;

public:
	//constructor
	Minion(Dictionary _charStats);
	//getters
	Dictionary getStats();
	void setFormationPlace(int x, int y);
	formationSpot getFormationPlace();
	int getCurrentHP();
	void attack(Minion& _objective);
	void getHurted(int damage);
	bool isDeath();
	//setters
};

