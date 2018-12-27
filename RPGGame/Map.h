#pragma once
enum MAPTYPE {MT_FOREST, MT_MOUNTAINS, MT_HOUSE, MT_CAVE, MT_CITY};
class Map
{
private:
	MAPTYPE place;
	bool chest;
	bool enemy;
	bool visited = false;
public:
	Map();
	void setCity();
	void setPlace();
	int getPlace();
	bool isChest();
	bool isEnemy();
	void visitPlace();
	~Map();
};
