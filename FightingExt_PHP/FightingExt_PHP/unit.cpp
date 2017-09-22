#include "unit.h"
#include "stdafx.h"

Unit::Unit(Minion* _minions, int arr_size, int _columnSize) {
	//assign minions pointer to internal var
	minions = _minions;
	size = arr_size;
	columnSize = _columnSize;
	//not so simple, ceil just round minions, not lines

	lineSize = std::ceil((float)size / (float)columnSize);
	//defining spot places for minions
	//minions[0].setFormationPlace(7, 7);
	int index = 0;
	for (int y = 0; y < lineSize; y++) {
		for (int x = 0; x < columnSize; x++) {
			//watch for out of boundaries
			if (index >= size) { break; };
			minions[index].setFormationPlace(x, y);
			index++;
		}
	}

	//defining hitboxes, minion have 1 meter width, 0.5 meter depth
	minionHitbox.topLeft.x = 0;
	minionHitbox.topLeft.y = 0;
	minionHitbox.bottRight.x = 1;
	minionHitbox.bottRight.y = -0.5;
	createUnitHitbox();
	//0,0 as start position
	position.x = 0;
	position.y = 0;
	//initialize up (0,1)
	up.x = 0;
	up.y = 1;
	//current direction=up;
	currentDir = up;
}

void Unit::createUnitHitbox() {
	unitHitbox.topLeft.x = 0;
	unitHitbox.topLeft.y = 0;
	unitHitbox.bottRight.x = minionHitbox.bottRight.x*columnSize;
	unitHitbox.bottRight.y = minionHitbox.bottRight.y*lineSize;
}
hitbox Unit::getUnitHitbox() {
	return unitHitbox;
}
dirVec Unit::getCurrDir() {
	return currentDir;
}
coord Unit::getPosition() {
	return position;
}

//Function that rotates the current direction var, it changes the internal vector
//for now, measured in degrees
void Unit::rotateDir(float angle) {
	//transform degrees in radians
	angle = angle * PI / 180.0;

	float rotatedX;
	float rotatedY;

	rotatedX = currentDir.x*cos(angle) - currentDir.y*sin(angle);
	rotatedY = currentDir.x*sin(angle) + currentDir.y*cos(angle);

	currentDir = { rotatedX,rotatedY };
}

void Unit::move(dirVec direction, float speed) {
	coord futurePos;
	futurePos.x = position.x + direction.x*speed;
	futurePos.y = position.y + direction.y*speed;
	position = futurePos;//position+direction;//*speed;
}

Minion& Unit::getMinion(int index) {
	return minions[index];
}
//just beginning, so some asumptions:
//unit's line are equal in size, and are facing each other,
// the first element fight with the last
//just 1 line for now
// 			unit1:	unit2:
//     		 0 > 	< last
//		middle > 	< middle
//			last > 	< 0
void Unit::combat(Unit& _enemyUnit) {
	for (int i = 0; i<columnSize; i++) {
		//attack!!!
		//taking minions by index will not make it, need a bit more complexity
		minions[i].attack(_enemyUnit.getMinion(columnSize - (i + 1)));
		if (minions[i].getCurrentHP <= 0) {
			//death, so need reforming
		}
	}
}

Unit::~Unit() {
	//delete minions;
}