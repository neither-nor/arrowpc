#pragma once
#include "stdafx.h"
struct Evt{
	char des[110];
	int tim;
	Evt(){

	}
	Evt(char *_des,int _tim){
		sprintf(des,"%s",_des);
		tim=_tim;
	}
};
class Evtlist{
public:
	Evtlist();
	~Evtlist();
	void add(char *evt);
	void Render();
private:
	char evnts[1010];
	Evt evtq[110];
	int evthd,evttl;
};

