#include "MOD.h"


MOD::MOD(void){
	g_pMesh=NULL;//��������
	g_vecMaterials.clear();//����
	g_dwMtrlNum=0;//��������
	g_vecPTextures.clear();//����
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
	//��ȡ���ʺ�����
	CHAR szTextureFile[MAX_PATH];
	if(NULL!=pMtrlBuffer && 0!=g_dwMtrlNum){
		LPD3DXMATERIAL	pMtrl=(LPD3DXMATERIAL)pMtrlBuffer->GetBufferPointer();
		for(DWORD i=0;i<g_dwMtrlNum;i++){
			pMtrl[i].MatD3D.Ambient=pMtrl[i].MatD3D.Diffuse;//���ò��ʶԻ�����ķ���
			g_vecMaterials.push_back(pMtrl[i].MatD3D);//��Ӳ���

			if(NULL!=pMtrl[i].pTextureFilename)//�����ļ�����Ϊ��
			{
				ZeroMemory(szTextureFile,sizeof(szTextureFile));
				sprintf(szTextureFile,"src/%s",pMtrl[i].pTextureFilename);
				LPDIRECT3DTEXTURE9 pTexture=NULL;
				D3DXCreateTextureFromFileA(Device,szTextureFile,&pTexture);//����������
				g_vecPTextures.push_back(pTexture);//�������
			}
			else
			{
				//��ͼ�ļ�Ϊ�գ������õ�ǰ����ΪNULL
				g_vecPTextures.push_back(NULL);
			}
		}
	}
	pMtrlBuffer->Release();
	
	//����������Ż������п���
	g_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT//�Ż���־���Ƴ����õĶ��������
													|D3DXMESHOPT_ATTRSORT//��������ID��������ͼԪ��������
													|D3DXMESHOPT_VERTEXCACHE,//��߶�����ٻ����������
													(DWORD *)pAdjBuffer->GetBufferPointer(),//ָ����δ�Ż���������ڽ������ָ��
													NULL,//�洢�Ż����������ڽ���Ϣ
													NULL,
													NULL);
	pAdjBuffer->Release();
	//�ж϶����Ƿ���з����������п���
	if(!(g_pMesh->GetFVF() & D3DFVF_NORMAL))
	{
		//û�з����������¡һ��
		LPD3DXMESH	pTempMesh=NULL;
		g_pMesh->CloneMeshFVF(D3DXMESH_MANAGED,
													g_pMesh->GetFVF()|D3DFVF_NORMAL,
													Device,
													&pTempMesh);//��¡����ʹ����з�����
		if(NULL!=pTempMesh)
		{
			D3DXComputeNormals(pTempMesh,NULL);//���㶥�㷨����
			g_pMesh->Release();
			g_pMesh=pTempMesh;
		}
	}

}

void MOD::Render(){
	for(DWORD i=0;i<g_dwMtrlNum;i++){
		Device->SetMaterial(&g_vecMaterials[i]);//���ò���
		Device->SetTexture(0,g_vecPTextures[i]);//��������
		g_pMesh->DrawSubset(i);//�����Ӽ�
	}
}