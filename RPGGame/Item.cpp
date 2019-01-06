#include "pch.h"
#include "Item.h"
#include <random>
#include <fstream>

Item::Item()
{
}

Item::Item(TYPE typ) {
	if (typ == T_FREESPACE) {
		this->typ = typ;
		this->needStr = 0;
		this->needDex = 0;
		this->needIn = 0;
		this->needSt = 0;
		this->needLu = 0;

		this->giveStr = 0;
		this->giveDex = 0;
		this->giveIn = 0;
		this->giveSt = 0;
		this->giveLu = 0;
	}
	else {
		Item(T_FREESPACE);
	}
}

Item::Item(TYPE typ, int forWho, string name, int needStr, int needDex, int needIn, int needSt, int needLu, int giveStr, int giveDex, int giveIn, int giveSt, int giveLu, int attStr, int armor, QUALITY quality)
{
	this->typ = typ;
	this->quality = quality;
	this->forWho = forWho;
	this->attStr = attStr;
	this->armor = armor;

	this->itemName = name;
	this->needStr = needStr;
	this->needDex = needDex;
	this->needIn = needIn;
	this->needSt = needSt;
	this->needLu = needLu;

	this->giveStr = giveStr;
	this->giveDex = giveDex;
	this->giveIn = giveIn;
	this->giveSt = giveSt;
	this->giveLu = giveLu;

}

TYPE Item::getType()
{
	return this->typ;
}

Item Item::generateRandomItem(int playerLevel) {


	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> levelRand(playerLevel,playerLevel+4);
	std::uniform_int_distribution<std::mt19937::result_type> typeRand(0,3);
	std::uniform_int_distribution<std::mt19937::result_type> qualityRand(1,20);
	std::uniform_int_distribution<std::mt19937::result_type> classRand(0,4);

	int level = levelRand(rng) - 2; //Losowy level itemka (+-2 od gracza)
	if (level < 1) {
		level = 1;
	}	//Gdy level mniejszy niz 1, to 1



	int x = 1 + level * 4 / static_cast<int>(quality + 1) / 3;
	if (x < level) x = level;

	TYPE type = static_cast<TYPE>(typeRand(rng)); // Losowy typ dropionego przedmiotu
	QUALITY quality;
	int qualityTemp = qualityRand(rng); //Losowo generuje jako�� przedmiotu. Szansa na �mie� 20%, na common 65%, na rare 10%, na legendaty 5%!
	if (qualityTemp > 4) {
		if (qualityTemp >= 18) {
			if (qualityTemp == 20) quality = Q_LEGENDARY;
			else quality = Q_RARE;
		}
		else quality = Q_COMMON;
	}
	else quality = Q_TRASH;

	int q; //modifier dla bi�uterii
	if (quality == Q_LEGENDARY) q = 3;
	if (quality == Q_RARE) q = 2;
	if (quality == Q_COMMON) q = 1;
	if (quality == Q_TRASH) q = 0;

	int forWho = classRand(rng);

	std::uniform_int_distribution<std::mt19937::result_type> randPerkq(1, level + q * 10);
	std::uniform_int_distribution<std::mt19937::result_type> randPerk(1, level + quality);
	std::uniform_int_distribution<std::mt19937::result_type> armorRand(level, level + level * 4);
	std::uniform_int_distribution<std::mt19937::result_type> attackRand(level, level + level * 4);
	std::uniform_int_distribution<std::mt19937::result_type> baseNeedRand(level, 1 + level * 4 / static_cast<int>(quality + 1)); //Glowny wymagany perk dla danej klasy - [level itema;levelItema*4/jakosc]
	std::uniform_int_distribution<std::mt19937::result_type> secondaryNeedRand(level, x); //Drugi perk dodatkowo



	int attStr = 0;
	int armor = 0;

	int needStr = 0;
	int needDex = 0;
	int needIn = 0;
	int needSt = 0;
	int needLu = 0;

	int givesStr = 0;
	int givesDex = 0;
	int givesIn = 0;
	int givesSt = 0;
	int givesLu = 0;

	string name = "name";

	ifstream swords("Swords.txt");
	ifstream bows("Bows.txt");
	ifstream daggers("Daggers.txt");
	ifstream wands("Wands.txt");
	ifstream orcStuff("OrcStuff.txt");
	ifstream armors("Armors.txt");
	ifstream rings("Rings.txt");
	ifstream necklaces("Necklaces.txt");
	




	switch (static_cast<int>(type)) {
	case 0: //Generates weapon
		attStr = attackRand(rng) / static_cast<int>(quality + 1); // Sila ataku to WYGENEROWANY ATAK podzielony przez jako�� + 1, czyli legendarka ma normalny, a smiec /4
		switch (forWho) {
		case 0:
			needStr = baseNeedRand(rng);
			needSt = secondaryNeedRand(rng);
			needIn = randPerk(rng);
			needDex = randPerk(rng);
			needLu = randPerk(rng);
			break;
		case 1:
			needDex = baseNeedRand(rng);
			needLu = secondaryNeedRand(rng);
			needIn = randPerk(rng);
			needStr = randPerk(rng);
			needLu = randPerk(rng);
			break;
		case 2:
			needIn = baseNeedRand(rng);
			needLu = secondaryNeedRand(rng);
			needSt = randPerk(rng);
			needStr = randPerk(rng);
			needDex = randPerk(rng);
			break;
		case 3:
			needSt = baseNeedRand(rng);
			needDex = secondaryNeedRand(rng);
			needIn = randPerk(rng);
			needStr = randPerk(rng);
			needLu = randPerk(rng);
			break;
		case 4:
			needLu = baseNeedRand(rng);
			needStr = secondaryNeedRand(rng);
			needIn = randPerk(rng);
			needDex = randPerk(rng);
			needLu = randPerk(rng);
			break;
		}
		break;
	case 1: //Random armor
		forWho = 5;
		armor = armorRand(rng) / static_cast<int>(quality+1);
		needIn = randPerk(rng) / static_cast<int>(quality + 1);
		needDex = randPerk(rng) / static_cast<int>(quality + 1);
		needLu = randPerk(rng) / static_cast<int>(quality + 1);
		needSt = randPerk(rng) / static_cast<int>(quality + 1);
		needStr = randPerk(rng) / static_cast<int>(quality + 1);
		break;
	case 2: //random Necklace
		forWho = 5;
		givesIn = randPerkq(rng) / static_cast<int>(quality + 1)+level/5;
		givesDex = randPerkq(rng) / static_cast<int>(quality + 1) + level / 5;
		givesLu = randPerkq(rng) / static_cast<int>(quality + 1) + level / 5;
		givesSt = randPerkq(rng) / static_cast<int>(quality + 1) + level / 5;
		givesStr = randPerkq(rng) / static_cast<int>(quality + 1) + level / 5;
		break;
	case 3: //random Ring
		forWho = 5;
		givesIn = randPerkq(rng) / static_cast<int>(quality + 1) + level / 5;
		givesDex = randPerkq(rng) / static_cast<int>(quality + 1) + level / 5;
		givesLu = randPerkq(rng) / static_cast<int>(quality + 1) + level / 5;
		givesSt = randPerkq(rng) / static_cast<int>(quality + 1) + level / 5;
		givesStr = randPerkq(rng) / static_cast<int>(quality + 1) + level / 5;
		break;
	}
	return Item(type,forWho,name,needStr,needDex,needIn,needSt,needLu,givesStr,givesDex,givesIn,givesSt,givesLu,attStr,armor,quality);
}

void Item::showItem(int playerClass){
	BLUE; cout << "Typ przedmiotu : "; WHITE;
	switch (static_cast<int>(this->typ)) {
	case 0:
		cout << "BRO�";
		break;
	case 1:
		cout << "PANCERZ";
		break;
	case 2:
		cout << "NASZYJNIK";
		break;
	case 3:
		cout << "PIER�CIE�";
		break;
	case 4:
		cout << "WOLNE MIEJSCE";
		break;
	}
	cout << endl;
	if ((static_cast<int>(this->typ)) != 4) {
		gotoxy(2, 6);
		BLUE; cout << "Nazwa: "; WHITE; cout << this->itemName << endl;
		if (typ == 0 || typ == 1) {
			gotoxy(2, 7);
			BLUE; cout << "Potrzebna sila : "; WHITE; cout << this->needStr << endl;
			gotoxy(2, 8);
			BLUE; cout << "Potrzebna zwinnosc : "; WHITE; cout << this->needDex << endl;
			gotoxy(2, 9);
			BLUE; cout << "Potrzebna inteligencja: "; WHITE; cout << this->needIn << endl;
			gotoxy(2, 10);
			BLUE; cout << "Potrzebna wytrzyma�o��: "; WHITE; cout << this->needSt << endl;
			gotoxy(2, 11);
			BLUE; cout << "Potrzebne szcz�cie: "; WHITE; cout << this->needLu << endl;
			if (typ == 0) {
				gotoxy(2, 12);
				BLUE; cout << "Warto�� ataku: "; WHITE; cout << this->attStr << endl;
			}
			else {
				gotoxy(2, 12);
				BLUE; cout << "Warto�� obrony: "; WHITE; cout << this->armor << endl;
			}
		}
		else {
			gotoxy(2, 7);
			BLUE; cout << "Daje sily : "; WHITE; cout << this->giveStr << endl;
			gotoxy(2, 8);
			BLUE; cout << "Daje zwinno�ci : "; WHITE; cout << this->giveDex << endl;
			gotoxy(2, 9);
			BLUE; cout << "Daje inteligencji: "; WHITE; cout << this->giveIn << endl;
			gotoxy(2, 10);
			BLUE; cout << "Daje wytrzyma�o�ci: "; WHITE; cout << this->giveSt << endl;
			gotoxy(2, 11);
			BLUE; cout << "Daje szcz�cia: "; WHITE; cout << this->giveLu << endl;
		}
		gotoxy(2, 13);
		BLUE; cout << "Jako�� przedmiotu: ";
		switch (this->quality) {
		case 0:
			PINK; cout << "LEGENDARNY" << endl;
			break;
		case 1:
			LIME; cout << "RZADKI" << endl;
			break;
		case 2:
			WHITE; cout << "PRZECI�TNY" << endl;
			break;
		case 3:
			GREY; cout << "�MIE�" << endl;
			break;
		}
		gotoxy(2, 14);
		BLUE; cout << "Wymagana klasa: "; WHITE;
		switch (this->forWho) {
		case 0:
			if (playerClass == forWho) {
				WHITE; cout << "WOJOWNIK";
			}
			else {
				RED; cout << "WOJOWNIK"; WHITE;
			}
			break;
		case 1:
			if (playerClass == forWho) {
				WHITE; cout << "�UCZNIK";
			}
			else {
				RED; cout << "�UCZNIK"; WHITE;
			}
			break;
		case 2:
			if (playerClass == forWho) {
				WHITE; cout << "MAG";
			}
			else {
				RED; cout << "MAG"; WHITE;
			}
			break;
		case 3:
			if (playerClass == forWho) {
				WHITE; cout << "Z�ODZIEJ";
			}
			else {
				RED; cout << "Z�ODZIEJ"; WHITE;
			}
			break;
		case 4:
			if (playerClass == forWho) {
				WHITE; cout << "SZAMAN";
			}
			else {
				RED; cout << "SZAMAN"; WHITE;
			}
			break;
		case 5:
			WHITE; cout << "KA�DY";
			break;
		}
		gotoxy(2, 15);
		BLUE; cout << "ZA�O�ONY: "; WHITE;
		switch (isItemEquiped()) {
			case true:
				GREEN; cout << "TAK"; WHITE;
				break;
			case false:
				cout << "NIE";
				break;
		}
	}
}

int Item::getGStr()
{
	return this->giveStr;
}

int Item::getNStr()
{
	return this->needStr;
}

int Item::getGDex()
{
	return this->giveDex;
}

int Item::getNDex()
{
	return this->needDex;
}

int Item::getGIn()
{
	return this->giveIn;
}

int Item::getNIn()
{
	return this->needIn;
}

int Item::getGSt()
{
	return this->giveSt;
}

int Item::getNSt()
{
	return this->needSt;
}

int Item::getGLu()
{
	return this->giveLu;
}

int Item::getNLu()
{
	return this->needLu;
}

int Item::getClass()
{
	return this->forWho;
}

int Item::getAttStr()
{
	return this->attStr;
}

int Item::getArmor()
{
	return this->armor;
}
void Item::equip() {
	this->isEquiped = true;
}
void Item::takeOff()
{
	this->isEquiped = false;
}
bool Item::isItemEquiped()
{
	return this->isEquiped;
}


Item::~Item()
{
}
