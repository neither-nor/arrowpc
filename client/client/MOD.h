#pragma once
#include "show.h"
using namespace std;

class MOD:public DX{
public:
	MOD(void);
	~MOD(void);
	void init(char *nm);
	void Render();
private:
	LPD3DXMESH g_pMesh;//��������
	std::vector<D3DMATERIAL9> g_vecMaterials;//����
	DWORD g_dwMtrlNum;//��������
	std::vector<LPDIRECT3DTEXTURE9>	g_vecPTextures;//����
};

