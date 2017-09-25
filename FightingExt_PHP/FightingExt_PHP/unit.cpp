#include "unit.h"
#include "stdafx.h"

Unit::Unit(Minion* _minions, int arr_size, int _columnSize) {
	//assign minions pointer to internal var
	minions = _minions;
	size = arr_size;
	columnSize = _columnSize;
	aliveSize = size;
	rowSize = std::ceil((float)size / (float)columnSize);
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
	for (int y = 0; y < rowSize; y++) {
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
//because they are in formation, only the first row can die*
//*not true, they could be being flanked
void Unit::reforming() {
	//just do the for loop for the living
	int index = 0;
	std::cout << "cuantos vivos" << aliveSize << std::endl;
	printDeathMatrix();
	//do by rows, makes sense
	for (int row = 0; row < rowSize-1; row++) {
		//check next row has replacements
		
		if (checkRowReplacements( row+1)) {//continue then
			//so now, we always hace replacement, so we can avoid some null checks

			//WATCH OUT, because the array changes dinamyc the above statement is NOT TRUE and leads to BUG
			
			int index = row*columnSize;

			for (int x = 0; x < columnSize; x++) {
				if (minions[index].isDeath()) {
					//need replacement
					Minion& buffMinion = getMinionByPlace(x, row + 1);
					int searcher = 1;
					while (buffMinion.isDeath()) {
						//first search x-1, then x+1, then x-2, then x+2... 
						searcher *= -1;
						buffMinion = getMinionByPlace(x + searcher, row + 1);
						if (searcher > 0) searcher++;
					}
					std::swap(minions[index], buffMinion);
				}
				index++;
			}
		}
		else {
			//finish reforming when last line is full of death MUAHAHA
			break;
		}
	}
	/*for (int i = 0; i < aliveSize; i++) {
		int posX = i%columnSize;
		int posY = i / columnSize;
		//pseudocode:
		//if last row is full of death minions -> exit
		if (minions[i].isDeath()) {
			//std::cout << "cambiando(" << minions[i].getFormationPlace().x<<","<< minions[i].getFormationPlace().y<<") por "<< getMinionByPlace(posX, posY + 1).getFormationPlace().x<<","<< getMinionByPlace(posX, posY + 1).getFormationPlace().y << std::endl;
			Minion& buffMinion = getMinionByPlace(posX, posY + 1);
			//restart posX
			posX = 0;
			while (buffMinion.isDeath()) {
				//if straightforward replacement is dead, what then?
				//then check all the minions on the back row, starting from left, sorry, it will get messy, but makes sense in a unit reforming rows
				buffMinion = getMinionByPlace(posX, posY + 1);
				posX++;
			}
			std::swap(minions[i], buffMinion);
		}
	}*/
	//reset formation:
	setFormation();

}
bool Unit::checkRowReplacements(int _rowIndex) {
	
	//check next row has someone alive or GTFO
	int startIndex = (_rowIndex)*columnSize;
	int endIndex = startIndex + columnSize;
	
	//it's a pain checking always the last irregular row ¬¬
	if (endIndex > size) endIndex = size;
	for (int i = startIndex; i < endIndex; i++) {
		if (!minions[i].isDeath()) return true;
	}
	
	return false;
}

/**
This function returns addres of minion based on position in formation, 
if minion doesn't exist return the last element of the array that is still alive
*/
Minion& Unit::getMinionByPlace(int x, int y) {
	int index = 0;
	
	int indexByPos = (y * columnSize) + x;//the index in the array based in coord
	std::cout << "este el indexbypos, si pasa de 25 malo" << indexByPos << std::endl;
	if (indexByPos >= size) {//out of bounds
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
	unitHitbox.bottRight.y = minionHitbox.bottRight.y*rowSize;
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
//just 1 row for now
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
void Unit::printDeathMatrix (){
	string rowString = "";
	string matrixString = "";
	int index = 0;
	for (int y = 0; y < rowSize; y++) {
		for (int x = 0; x < columnSize; x++) {
			//remember check out of bounds (stupid irregular matrix)
			if (index >= size) break;
			rowString = rowString + std::to_string(minions[index].isDeath());
			index++;
		}
		rowString += "\n";
	}
	std::cout << rowString << std::endl;
}
Unit::~Unit() {
	//delete minions;
}