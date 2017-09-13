#include "MOD.h"


MOD::MOD(void){
	g_pMesh=NULL;//物体网格
	g_vecMaterials.clear();//材质
	g_dwMtrlNum=0;//材质数量
	g_vecPTextures.clear();//纹理
}


MOD::~MOD(void){
	
}

void MOD::init(char *nm){
	HRESULT hr=E_FAIL;
	LPD3DXBUFFER pAdjBuffer=NULL,pMtrlBuffer=NULL;
	char adr[110];
	sprintf(adr,"src/%s",nm);
	hr=D3DXLoadMeshFromX(adr,D3DXMESH_MANAGED,Device,&pAdjBuffer,&pMtrlBuffer,NULL,&g_dwMtrlNum,&g_pMesh);
	if(FAILED(hr)){
		MessageBox(0,"Mod init error",0,0);
	}
	//获取材质和纹理
	CHAR szTextureFile[MAX_PATH];
	if(NULL!=pMtrlBuffer && 0!=g_dwMtrlNum){
		LPD3DXMATERIAL	pMtrl=(LPD3DXMATERIAL)pMtrlBuffer->GetBufferPointer();
		for(DWORD i=0;i<g_dwMtrlNum;i++){
			pMtrl[i].MatD3D.Ambient=pMtrl[i].MatD3D.Diffuse;//设置材质对环境光的反射
			g_vecMaterials.push_back(pMtrl[i].MatD3D);//添加材质

			if(NULL!=pMtrl[i].pTextureFilename)//纹理文件名不为空
			{
				ZeroMemory(szTextureFile,sizeof(szTextureFile));
				sprintf(szTextureFile,"src/%s",pMtrl[i].pTextureFilename);
				LPDIRECT3DTEXTURE9 pTexture=NULL;
				D3DXCreateTextureFromFileA(Device,szTextureFile,&pTexture);//创建新纹理
				g_vecPTextures.push_back(pTexture);//添加纹理
			}
			else
			{
				//贴图文件为空，则设置当前纹理为NULL
				g_vecPTextures.push_back(NULL);
			}
		}
	}
	pMtrlBuffer->Release();
	
	//对网格进行优化，可有可无
	g_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT//优化标志，移除无用的顶点和索引
													|D3DXMESHOPT_ATTRSORT//根据属性ID对三角形图元进行排序
													|D3DXMESHOPT_VERTEXCACHE,//提高顶点高速缓存的命中率
													(DWORD *)pAdjBuffer->GetBufferPointer(),//指向尚未优化的网格的邻接数组的指针
													NULL,//存储优化后的网格的邻接信息
													NULL,
													NULL);
	pAdjBuffer->Release();
	//判断顶点是否具有法向量，可有可无
	if(!(g_pMesh->GetFVF() & D3DFVF_NORMAL))
	{
		//没有法向量，则克隆一分
		LPD3DXMESH	pTempMesh=NULL;
		g_pMesh->CloneMeshFVF(D3DXMESH_MANAGED,
													g_pMesh->GetFVF()|D3DFVF_NORMAL,
													Device,
													&pTempMesh);//克隆网格，使其具有法向量
		if(NULL!=pTempMesh)
		{
			D3DXComputeNormals(pTempMesh,NULL);//计算顶点法向量
			g_pMesh->Release();
			g_pMesh=pTempMesh;
		}
	}

}

void MOD::Render(){
	for(DWORD i=0;i<g_dwMtrlNum;i++){
		Device->SetMaterial(&g_vecMaterials[i]);//设置材质
		Device->SetTexture(0,g_vecPTextures[i]);//设置纹理
		g_pMesh->DrawSubset(i);//绘制子集
	}
}