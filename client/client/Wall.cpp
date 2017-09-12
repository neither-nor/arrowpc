#include "Wall.h"
bool Wall::inited=0;
LPDIRECT3DVERTEXBUFFER9 Wall::VB=NULL;
D3DMATERIAL9 Wall::mtrl; 
Wall::~Wall(){
	
}
Wall::Wall(){
	if(inited){
		return ;
	}
	inited=1;

	VERTEX1 vertexes[] = {
		//front
		{0.f,2.f,0.f,0.f,0.f,-1.f},
		{0.f,0.f,0.f,0.f,0.f,-1.f},
		{1.f,2.f,0.f,0.f,0.f,-1.f},
		{1.f,0.f,0.f,0.f,0.f,-1.f},
		//right
		{1.f,2.f,0.f,1.f,0.f,0.f},
		{1.f,0.f,0.f,1.f,0.f,0.f},
		{1.f,2.f,1.f,1.f,0.f,0.f},
		{1.f,0.f,1.f,1.f,0.f,0.f},
		//back
		{1.f,2.f,1.f,0.f,0.f,1.f},
		{1.f,0.f,1.f,0.f,0.f,1.f},
		{0.f,2.f,1.f,0.f,0.f,1.f},
		{0.f,0.f,1.f,0.f,0.f,1.f},
		//left
		{0.f,2.f,0.f,-1.f,0.f,0.f},
		{0.f,0.f,0.f,-1.f,0.f,0.f},
		{0.f,2.f,1.f,-1.f,0.f,0.f},
		{0.f,0.f,1.f,-1.f,0.f,0.f},
		//up
		{0.f,2.f,1.f,0.f,1.f,0.f},
		{0.f,2.f,0.f,0.f,1.f,0.f},
		{1.f,2.f,1.f,0.f,1.f,0.f},
		{1.f,2.f,0.f,0.f,1.f,0.f},
		//bottom
		{0.f,0.f,1.f,0.f,-1.f,0.f},
		{0.f,0.f,0.f,0.f,-1.f,0.f},
		{1.f,0.f,1.f,0.f,-1.f,0.f},
		{1.f,0.f,0.f,0.f,-1.f,0.f}
	};
	Device->CreateVertexBuffer( sizeof(vertexes)
		, 0
		, FVF_VERTEX1
		, D3DPOOL_DEFAULT
		, &VB
		, NULL );

	void *pvertexes = NULL;
	VB->Lock(0, sizeof(vertexes), (void**)&pvertexes, 0);
	memcpy(pvertexes, vertexes, sizeof(vertexes));
	VB->Unlock();
 
    ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));  
    //漫反射光  
    mtrl.Diffuse.r  = 1.0f;  
    mtrl.Diffuse.g  = 1.0f;  
    mtrl.Diffuse.b  = 0.0f;  
    mtrl.Diffuse.a  = 1.0f;  
    //环境光  
    mtrl.Ambient.r = .8f;  
    mtrl.Ambient.g = .8f;  
    mtrl.Ambient.b = 0.0f;  
    mtrl.Ambient.a = 1.0f;  
    //镜面反射光  
    mtrl.Specular.r = 1.0f;  
    mtrl.Specular.g = 1.0f;  
    mtrl.Specular.b = 1.0f;  
    mtrl.Specular.a = 1.0f;  
    mtrl.Power = 25.0f;  
}
void Wall::Render(){
	preSet();
	Device->SetMaterial(&mtrl);
	Device->SetStreamSource(0,VB,0,sizeof(VERTEX1));  
	Device->SetFVF(FVF_VERTEX1);  
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP,4,2);
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP,8,2);
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP,12,2);
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP,16,2);
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP,20,2);
}