#include "Show.h"

IDirect3DDevice9* DX::Device;
IDirect3D9* DX::d3d9;
int Show::nowt;
float Entity_3d::camx;
float Entity_3d::camz;
bool Entity_3d::Inited;
D3DLIGHT9 Entity_3d::light;
float Show::Mousex;
float Show::Mousey;
RECT DX::g_client_rect;
DX::DX(){

}
Show::Show(){
	rot=rotx=rotz=0;
	posx=posy=posz=0;
	scx=scy=scz=1.f;
}

Entity_3d::Entity_3d(){
	if(Inited){
		return ;
	}
	Inited=1;
	D3DXVECTOR3 vecDir; 
    ZeroMemory(&light, sizeof(D3DLIGHT9));
    //类型：
    light.Type = D3DLIGHT_DIRECTIONAL;  
    //漫反射光  
    light.Diffuse.r = 1.0f;   
    light.Diffuse.g = 1.0f;  
    light.Diffuse.b = 1.0f;  
    light.Diffuse.a = 1.0f;  
    //镜面光  
    light.Specular.r = 1.0f;  
    light.Specular.g = 1.0f;  
    light.Specular.b = 1.0f;  
    light.Specular.a = 1.0f;  
    //光的方向  
	light.Range = 1000.0f; 
	//vecDir=D3DXVECTOR3(-.2f,-.5f,1.f);
	vecDir=D3DXVECTOR3(-1.f,-3.f,2.f);
    //归一化方向  
    D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);  
}

bool DX::initD3d(HWND &hWnd){
	if(NULL==(d3d9=Direct3DCreate9(D3D_SDK_VERSION))){
		return false;
	}
	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;  
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;  
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;  
    d3dpp.BackBufferWidth = SCREEN_WIDTH;  
    d3dpp.BackBufferHeight = SCREEN_HEIGHT;  
    d3dpp.EnableAutoDepthStencil = TRUE;  
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;  
	d3dpp.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
	if(FAILED(d3d9->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&Device))){
		return false;
	}
	Device->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
	Device->SetRenderState(D3DRS_ZENABLE,TRUE);
	GetClientRect(hWnd,&g_client_rect);
	return true;
}

void Entity_Screen::preSet(){

}

void Entity_3d::preSet(){

	D3DXMATRIXA16 matWorld,matmv,matrt,matrtx,matrtz,matsc;
	D3DXMatrixRotationY(&matrt,rot);
	D3DXMatrixRotationX(&matrtx,rotx);
	D3DXMatrixRotationZ(&matrtz,rotz);
	D3DXMatrixTranslation(&matmv,posx,posy,posz);
	D3DXMatrixScaling(&matsc,scx,scy,scz);
	matWorld=matsc*matrtx*matrtz*matrt*matmv;
	Device->SetTransform(D3DTS_WORLD,&matWorld);

    D3DXVECTOR3 vEyePt(camx,15.0f,camz-10.0f);
    D3DXVECTOR3 vLookatPt(camx,0,camz);
    D3DXVECTOR3 vUpVec(0.0f,1.0f,0.0f);
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
    Device->SetTransform(D3DTS_VIEW, &matView);

    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH(&matProj,D3DX_PI/4,(FLOAT)SCREEN_WIDTH/(FLOAT)SCREEN_HEIGHT, 1.0f, 100.0f);
    Device->SetTransform(D3DTS_PROJECTION, &matProj);

	Device->SetLight(0,&light);
    Device->LightEnable(0,TRUE);
    Device->SetRenderState(D3DRS_LIGHTING,TRUE);
    Device->SetRenderState(D3DRS_AMBIENT,D3DCOLOR_XRGB(100, 100, 100));
	Device->SetRenderState(D3DRS_SPECULARENABLE,TRUE);
}

DX::~DX(){
	
}
Show::~Show(){

}
Entity_3d::~Entity_3d(){

}