#pragma once
#include "show.h"
#include "MOD.h"
class Arrow :public Entity_3d{
public:
	Arrow();
	~Arrow();
	Arrow(float _posx,float _posz,float _spdx,float _spdz,float _rot,int _bel,int _id);
	virtual void Render();
	int bel;
	static bool inited;
private:
	void init();
	float spdx,spdz;
	float lst;
	static MOD mod;
};
