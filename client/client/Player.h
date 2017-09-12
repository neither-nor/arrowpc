#pragma once
#include "show.h"
#include "MOD.h"
#include "HealthPoint.h"
class Player:public Entity_3d{
public:
	Player();
	Player(char *nm);
	~Player();
	void init();
	virtual void Render();
	char nickname[30];
	int hp;
	int lev;
	int exp;
private:
	LPD3DXMESH TextMesh;
	static MOD mod;
	static bool inited;
	HealthPoint hps;
	static D3DMATERIAL9 mtrlfont;
};

