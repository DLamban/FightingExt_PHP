// FightingExtPHP.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <conio.h>
#include "unit.h"
#include "minion.h"

int main()
{
	std::map<std::string, int> mapStats;
	mapStats["maxHP"] = 50;
	mapStats["strength"] = 12;
	mapStats["dexterity"] = 4;
	mapStats["height"] = 230;
	mapStats["weight"] = 120;
	mapStats["discipline"] = 9;
	mapStats["stamina"] = 14;
	mapStats["ranged"] = 1;
	mapStats["armour"] = 6;
	mapStats["speed"] = 8;
	Minion minion(mapStats);

	//changing stats a bit to generate different minion
	mapStats["strength"] = 9;
	mapStats["maxHP"] = 60;

	Minion minion2(mapStats);

	Minion minions[25] = {
		minion,minion2,minion,minion2,minion,
		minion,minion2,minion,minion2,minion,
		minion,minion2,minion,minion2,minion,
		minion,minion2,minion,minion2,minion,
		minion,minion2,minion,minion2,minion
	};
	int minionSize = (sizeof(minions) / sizeof(*minions));
	Unit unit(minions, minionSize, 7);
	Unit unit2(minions, minionSize, 7);
	//unit.getMinion(0).attack(unit.getMinion(1));
	/*std::cout<<unit.getUnitHitbox().topLeft.x<<std::endl;
	std::cout<<unit.getUnitHitbox().topLeft.y<<std::endl;
	std::cout<<unit.getUnitHitbox().bottRight.x<<std::endl;
	std::cout<<unit.getUnitHitbox().bottRight.y<<std::endl;*/
	//  std::cout<<(sizeof(minions)/sizeof(*minions))<<std::endl;
	//unit2.getMinion(0).setFormationPlace(4,4);
	//unit2.setFormationPlace(0);
	for (int i = 0; i<minionSize; i++) {
		std::cout << "el hp deste es" << unit2.getMinion(i).getCurrentHP() << "situado en x:" << unit2.getMinion(i).getFormationPlace().x << "y situado en y:" << unit2.getMinion(i).getFormationPlace().y << std::endl;
	}
	unit.combat(unit2);
	std::cout << "despues del combate" << std::endl;
	/*for (int i=0;i<minionSize;i++){
	std::cout<<"el hp deste es" <<unit2.getMinion(i).getCurrentHP()<<std::endl;
	}*/
	//wait for input boy
	_getch();
	return 0;
}

