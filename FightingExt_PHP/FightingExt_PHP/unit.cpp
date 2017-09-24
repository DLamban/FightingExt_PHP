#include "unit.h"
#include "stdafx.h"

Unit::Unit(Minion* _minions, int arr_size, int _columnSize) {
	//assign minions pointer to internal var
	minions = _minions;
	size = arr_size;
	columnSize = _columnSize;
	aliveSize = size;
	lineSize = std::ceil((float)size / (float)columnSize);
	setFormation();
	

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
void Unit::setFormation() {
	//defining spot places for minions
	int index = 0;
	for (int y = 0; y < lineSize; y++) {
		for (int x = 0; x < columnSize; x++) {
			//watch for out of boundaries
			if (index >= size) { break; };
			minions[index].setFormationPlace(x, y);
			index++;
		}
	}
}
void Unit::killMinion() {
	aliveSize--;
}
//It's totally imposible to have a perfect algorithm that works in all the cases, so use more than 1 algorithm
//replace the dead minions with fresh from behind
//because they are in formation, only the first line can die*
//*not true, they could be being flanked
void Unit::reforming() {
	//just do the for loop for the living
	int index = 0;
	std::cout << "cuantos vivos" << aliveSize << std::endl;
	
	for (int i = 0; i < aliveSize; i++) {
		int posX = i%columnSize;
		int posY = i / columnSize;
		if (minions[i].isDeath()) {
			std::cout << "cambiando(" << minions[i].getFormationPlace().x<<","<< minions[i].getFormationPlace().y<<") por "<< getMinionByPlace(posX, posY + 1).getFormationPlace().x<<","<< getMinionByPlace(posX, posY + 1).getFormationPlace().y << std::endl;
			if (getMinionByPlace(posX, posY + 1).isDeath()) break;//this break was so necessary, don't change dead for dead
			std::swap(minions[i], getMinionByPlace(posX, posY + 1));
		}
	}
	//reset formation:
	setFormation();

}

/**
This function returns addres of minion based on position in formation, 
if minion doesn't exist return the last element of the array that is still alive
*/
Minion& Unit::getMinionByPlace(int x, int y) {
	int index = 0;
	
	int indexByPos = (y * columnSize) + x;//the index in the array based in coord
	
	if (indexByPos > size) {//out of bounds
		//start at last element of the array
		index = size - 1;
		//error if everyone is dead
		while (minions[index].isDeath()) {
			index--;
		}
		return minions[index];
	}
	//start from the beggining
	index = 0;
	while (index < size) {
		if (minions[index].getFormationPlace().x == x && minions[index].getFormationPlace().y == y) return  minions[index] ;
		index++;
	}
	
	
	
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
		int enemyIndex = columnSize - (i + 1);
		Minion& enemyMinion = _enemyUnit.getMinion(enemyIndex);

		minions[i].attack(enemyMinion);
		//need events to set the death flag
		if (enemyMinion.isDeath()) {
			_enemyUnit.killMinion();
		}
		
	}
}

Unit::~Unit() {
	//delete minions;
}