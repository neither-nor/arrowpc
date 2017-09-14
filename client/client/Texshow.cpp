#include "Texshow.h"

bool Texshow::inited=0;
LPDIRECT3DTEXTURE9 Texshow::weapon_tex[10];
Texshow::Texshow(){
	
}


Texshow::~Texshow(){
	if(VB!=NULL){
		VB->Release();
	}
}
void Texshow::init(float x,float y,float X,float Y){
	if(!inited){
		inited=1;
		int i;
		for(i=1;i<=2;i++){
			char t[30];
			sprintf(t,"src/weapon%d.jpg",i);
			if(FAILED(D3DXCreateTextureFromFile(Device,t,&weapon_tex[i]))){
				MessageBox(0,"!",0,0);
			}
		}
	}
	VERTEX3 vertexes[] ={
		{x,y,0.f,1.f,0.f,0.f},
		{x,y+Y,0.f,1.f,0.f,1.f},
		{x+X,y,0.f,1.f,1.f,0.f},
		{x+X,y+Y,0.f,1.f,1.f,1.f}
	};
	Device->CreateVertexBuffer(sizeof(vertexes)
		,0
		,FVF_VERTEX3
		,D3DPOOL_DEFAULT
		,&VB
		,NULL);

	void *pvertexes = NULL;
	VB->Lock(0,sizeof(vertexes),(void**)&pvertexes,0);
	memcpy(pvertexes,vertexes,sizeof(vertexes));
	VB->Unlock();
}
void Texshow::Refresh(){

}
void Texshow::Render(){
	LPDIRECT3DTEXTURE9* p;
	if(cls==TEXCLS_WEAPON){
		p=weapon_tex;
	}
	Device->SetTexture(0,p[frm]);
	Device->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	Device->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);

	Device->SetStreamSource(0,VB,0,sizeof(VERTEX3));
	Device->SetFVF(FVF_VERTEX3);

	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

}