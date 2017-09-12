#pragma once
#include "Show.h"
class HealthPoint:public Entity_3d{
public:
	HealthPoint();
	~HealthPoint();
	static bool inited;
	static LPDIRECT3DVERTEXBUFFER9 VB;
	float hp;
	virtual void Render();
};

