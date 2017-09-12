#include "HealthPoint.h"

bool HealthPoint::inited=0;
LPDIRECT3DVERTEXBUFFER9 HealthPoint::VB;

HealthPoint::HealthPoint(){
	if(inited){
		return;
	}
	inited=1;
	//*
	VERTEX2 vertexes[] ={
		{-1.25f,2.7f,.1f,D3DCOLOR_XRGB(255,0,0)},
		{-1.25f,2.6f,0.f,D3DCOLOR_XRGB(255,0,0)},
		{1.25f,2.7f,.1f,D3DCOLOR_XRGB(255,0,0)},
		{1.25f,2.6f,0.f,D3DCOLOR_XRGB(255,0,0)}
	};
	//*/
	Device->CreateVertexBuffer(sizeof(vertexes)
		,0
		,FVF_VERTEX2
		,D3DPOOL_DEFAULT
		,&VB
		,NULL);

	void *pvertexes = NULL;
	VB->Lock(0,sizeof(vertexes),(void**)&pvertexes,0);
	memcpy(pvertexes,vertexes,sizeof(vertexes));
	VB->Unlock();
}


HealthPoint::~HealthPoint(){
	
}

void HealthPoint::Render(){
	scx=hp;
	preSet();
	Device->SetRenderState(D3DRS_LIGHTING,FALSE);
	Device->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_FLAT);
	Device->SetFVF(FVF_VERTEX2);
	Device->SetStreamSource(0,VB,0,sizeof(VERTEX2));
	
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}
