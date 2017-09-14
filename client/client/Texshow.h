#pragma once
#include "Show.h"
#define TEXCLS_WEAPON 1
class Texshow:
	public Entity_Screen
{
public:
	int cls;
	int frm;
	static bool inited;
	static LPDIRECT3DTEXTURE9 weapon_tex[10];
	virtual void Render();
	virtual void Refresh();
	LPDIRECT3DVERTEXBUFFER9 VB;
	void init(float x,float y,float X,float Y);
	Texshow();
	virtual ~Texshow();
};

