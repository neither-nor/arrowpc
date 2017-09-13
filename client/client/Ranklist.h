#pragma once
#include "stdafx.h"
struct Rklst{
	char name[110];
	int kil;
	int id;
	friend bool operator <(Rklst x,Rklst y){
		return x.kil!=y.kil?x.kil>y.kil:x.id>y.id;
	}
};
class Ranklist{
public:
	Ranklist();
	~Ranklist();
	void Render();
	void add(char *nam,int kil,int id);
	void clr();
private:
	int cnt;
	Rklst rk[110];
	char rklist[1010];
};

