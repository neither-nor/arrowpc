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
	LPD3DXMESH g_pMesh;//物体网格
	std::vector<D3DMATERIAL9> g_vecMaterials;//材质
	DWORD g_dwMtrlNum;//材质数量
	std::vector<LPDIRECT3DTEXTURE9>	g_vecPTextures;//纹理
};

