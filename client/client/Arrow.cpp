#include "Arrow.h"
bool Arrow::inited=0;
MOD Arrow::mod;
void Arrow::init(){
	mod.init("arrow.x");
}
Arrow::~Arrow(){

}
Arrow::Arrow(){
	if(inited){
		return ;
	}
	inited=1;
	init();
}
Arrow::Arrow(float _posx,float _posz,float _spdx,float _spdz,float _rot,int _bel,int _id){
	posx=_posx;
	posz=_posz;
	posy=.5f;
	spdx=_spdx;
	spdz=_spdz;
	rot=_rot;
	lst=nowt;
	bel=_bel;
	eid=_id;
	typ="arrow";
	if(!inited){
		inited=1;
		init();
	}
}
void Arrow::Render(){
	preSet();
	mod.Render();
}

void Arrow::Refresh(){
	posx+=spdx*(nowt-lst)/1000;
	posz+=spdz*(nowt-lst)/1000;
	lst=nowt;
}