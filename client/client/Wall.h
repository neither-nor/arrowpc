#pragma once
#include "Show.h"
class Wall:public Entity_3d{
public:
	Wall();
	~Wall();
	virtual void Render();
private:
	static bool inited;
	static LPDIRECT3DVERTEXBUFFER9 VB;
	static D3DMATERIAL9 mtrl;
};