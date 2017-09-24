
#pragma once
#include "minion.h"
#define PI 3.14159265
#include <cmath>
typedef struct dirVec {
	//for now float precision , I think is more than enough, but I'll test later
	float x;
	float y;
} dirVec;

typedef struct coord {
	float x;
	float y;
} coord;

typedef struct hitbox {
	coord topLeft;
	coord bottRight;
} hitbox;

class Unit {
private:
	int size;
	int aliveSize;
	hitbox minionHitbox;
	hitbox unitHitbox;
	int columnSize;
	//linesize is size/columnSize as int
	int lineSize;
	Minion* minions;
	//Direction vector
	dirVec up;
	dirVec currentDir;
	coord position;
public:
	//constructor
	void killMinion();
	void setFormation();
	Minion& getMinion(int index);
	Minion& getMinionByPlace(int x, int y);
	Unit(Minion* minions, int arr_size, int _columnSize);
	void createUnitHitbox();
	hitbox getUnitHitbox();
	void combat(Unit& _enemyUnit);
	dirVec getCurrDir();
	void rotateDir(float an);
	coord getPosition();
	void move(dirVec direction, float speed);
	void reforming();
	~Unit();  // DON'T FORGET TO FREE UP SPACE!
};
