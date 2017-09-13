#pragma once
#include<d3dx9.h>
#include<Windows.h>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include<queue>
#include<map>
#include<bitset>
#include<stack>
#include<vector>
#include<set>
#include<string.h>
#include<cstring>
using namespace std;

const int SCREEN_WIDTH=700;
const int SCREEN_HEIGHT=700;


struct VERTEX1{
    float x,y,z;
	float nx,ny,nz;
};
#define FVF_VERTEX1 (D3DFVF_XYZ|D3DFVF_NORMAL)
struct VERTEX2{
	float x,y,z;
	DWORD color;
};
#define FVF_VERTEX2 (D3DFVF_XYZ|D3DFVF_DIFFUSE)

class DX{
public:
	DX();
	virtual ~DX();
	static IDirect3DDevice9* Device;
	static IDirect3D9* d3d9;
	static RECT g_client_rect;
	static bool initD3d(HWND &hWnd);
};

class Show:public DX{
public:
	Show(void);
	virtual ~Show();
	static int nowt;
	virtual void Render()=0;
	virtual void Refresh()=0;
	float posx,posz,posy;
	float rot;
	float rotx,rotz;
	float scx,scy,scz;
	static float Mousex;
	static float Mousey;
	int eid;
	string typ;
protected:
	virtual void preSet()=0;
};

class Entity_Screen:public Show{
public:
	virtual void preSet();
	virtual void Render()=0;
	virtual void Refresh()=0;
};

class Entity_3d:public Show{
public:
	Entity_3d();
	virtual ~Entity_3d();
	static float camx;
	static float camz;
	virtual void preSet();
	virtual void Render()=0;
	virtual void Refresh();
	static bool Inited;
private:
	static D3DLIGHT9 light;
};
