#include "minion.h"
#include "stdafx.h"
//I use a dictionary for clarity
Minion::Minion(Dictionary _charStats) {
	charStats = _charStats;
	death = false;
	//hmm, I think I could automatize this
	//maybe some vars derivated from other vars, but first thing first
	currentHP = charStats["maxHP"];//yes, currentHp is MaxHp at construction time
	strength = charStats["strength"];
	dex = charStats["dexterity"];
	height = charStats["height"];
	weight = charStats["weight"];
	discipline = charStats["discipline"];
	stamina = charStats["stamina"];
	ranged = charStats["ranged"];
	armour = charStats["armour"];
	speed = charStats["speed"];
}
void Minion::setFormationPlace(int x, int y) {
	formationPlace.x = x;
	formationPlace.y = y;
}

formationSpot Minion::getFormationPlace() {
	return formationPlace;
}

int Minion::getCurrentHP() {
	if (currentHP <= 0) {
		death = true;
	}
	return currentHP;
}
bool Minion::isDeath() {
	return death;
}
//first encounter with addresses with C++, remember, without & it calls a copy!
void Minion::attack(Minion& _objective) {
	int damage = strength + rand() % 5;
	_objective.getHurted(damage);
}

void Minion::getHurted(int _damage) {
	currentHP -= _damage;
}

Dictionary Minion::getStats() {
	//return the values defined at construction, so it's not very flexible
	return charStats;
}
