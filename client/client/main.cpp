#include<WinSock2.h>
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
#include "Show.h"
#include "Wall.h"
#include "Player.h"
#include "Arrow.h"
#include "TCPtransport.h"
#include "TXT.h"
#include "Evtlist.h"
#include "Ranklist.h"
#include "Texshow.h"
using namespace std;
TCPtransport tcp;
Show *p[5010];
set<int>Sd;
int n;
bool down[210];
char buf[10010];
char nickname[110];
int nicknamelen;
float rot;
Player* ply[110];
char S[10010];
char* s[10010];
int etot;
char mp[110][110];
int id;
set<int>liv;
int lst;
Evtlist evtlist;
Ranklist ranklist;
int gamestat;
int lstattack;
Texshow weaponbox;
float sqr(float x){
	return x*x;
}
float dis(float x,float y,float xx,float yy){
	return sqrt(sqr(x-xx)+sqr(y-yy));
}
void init(){
	int i,j;
	tcp.init("106.14.159.92",81);
//	tcp.init("218.62.22.209",233);
	weaponbox.init(250,625,50,50);
	weaponbox.cls=TEXCLS_WEAPON;
	ply[0]=new Player("system");
	tcp.send("nickname",0,-100.f,-100.f,0.f,0,0);
	ZeroMemory(buf,10010);
	tcp.recv();
	memcpy(S,tcp.GetBuf,sizeof(S));
	sscanf(S,"%*s%d",&id);
	etot=id*100000;
	for(i=1;i<=30;i++){
		for(j=1;j<=30;j++){
			mp[i][j]=S[(i-1)*30+j-1];
			if(mp[i][j]=='#'){
				p[n]=new Wall();
				p[n]->posx=i;
				p[n]->posz=j;
				n++;
			}
		}
	}
	int tstx=rand()%30+1,tstz=rand()%30+1;
	while(mp[tstx][tstz]=='#'){
		tstx=rand()%30+1;
		tstz=rand()%30+1;
	}
	Entity_3d::camx=tstx;
	Entity_3d::camz=tstz;
	lst=clock();
	tcp.LEN=0;
	ply[id]=new Player("new birth");
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
	if(gamestat==0){
		if(msg==WM_PAINT){
			ValidateRect(hWnd,NULL);
		}
		if(msg==WM_DESTROY){
			PostQuitMessage(0);
		}
		if(msg==WM_KEYDOWN){
			if(wParam>='A'&&wParam<='Z'){
				if(nicknamelen<=10){
					nickname[nicknamelen++]=wParam-'A'+'a';
				}
			}
			if(wParam==8){
				if(nicknamelen){
					nickname[--nicknamelen]=0;
				}
			}
			if(wParam==13){
				init();
				gamestat=1;
			}
		}
	}else if(gamestat==1){
		switch(msg){
			case WM_PAINT:{
				ValidateRect(hWnd,NULL);
			}break;
			case WM_DESTROY:{
				PostQuitMessage(0);
			}break;
			case WM_KEYDOWN:{
				down[wParam]=1;
			}break;
			case WM_KEYUP:{
				down[wParam]=0;
			}break;
			case WM_LBUTTONDOWN:{
				if(ply[id]->weapon==1){
					if(clock()-lstattack>500){
						lstattack=clock();
						sprintf(buf,"add arrow %f %f %f %f %f %d %d",Entity_3d::camx+cos(rot)*1.5,Entity_3d::camz-sin(rot)*1.5,cos(rot)*7.f,-sin(rot)*7.f,rot,++etot,id);
						tcp.add(buf);
					}
				}
				else if(ply[id]->weapon==2){
					if(clock()-lstattack>1000){
						lstattack=clock();
						for(set<int>::iterator it=liv.begin();it!=liv.end();it++){
							if((*it)!=id&&dis(ply[*it]->posx,ply[*it]->posz,ply[id]->posx,ply[id]->posz)<2){
								sprintf(buf,"damage %d %d %d",*it,2,id);
								tcp.add(buf);
							}
						}
					}
				}
			}break;
		}
	}
	return ::DefWindowProc(hWnd,msg,wParam,lParam);
}
void Render(){
	Show::Device->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(155,155,0),1.0f,0);
	Show::Device->BeginScene();
	int i;
	
	set<int>::iterator it;
	for(i=0;i<n;i++){
		p[i]->Render();
	}
	for(it=liv.begin();it!=liv.end();it++){
		ply[*it]->Render();
	}
	evtlist.Render();
	ranklist.Render();
	weaponbox.frm=ply[id]->weapon;
	weaponbox.Render();
	Show::Device->EndScene();
	Show::Device->Present(NULL,NULL,NULL,NULL);
}
int getint(int &i){
	int re;
	sscanf(s[++i],"%d",&re);
	return re;
}
float getfloat(int &i){
	float re;
	sscanf(s[++i],"%f",&re);
	return re;
}
void chkdead(int damfrom){
	if(ply[id]->hp<=0){
		sprintf(buf,"kill %d %d",damfrom,id);
		tcp.add(buf);
		ply[id]->hp=1;
		ply[id]->exp=0;
		ply[id]->lev=1;
		ply[id]->weapon=1;
		ply[id]->skill1=0;
		ply[id]->skill2=0;
		int x=rand()%30+1;
		int y=rand()%30+1;
		while(mp[x][y]=='#'){
			x=rand()%30+1;
			y=rand()%30+1;
		}
		ply[id]->posx=x;
		ply[id]->posz=y;
		Entity_3d::camx=x;
		Entity_3d::camz=y;
	}
}
void Communicate(){
	int i;
	tcp.send(nickname,id,Entity_3d::camx,Entity_3d::camz,rot,ply[id]->hp,ply[id]->kil);
	ZeroMemory(buf,10010);
	tcp.recv();
	memcpy(S,tcp.GetBuf,sizeof(S));
	int tot=0;
	s[tot=1]=&S[0];
	for(i=0;S[i];i++){
		if(S[i]==' '||S[i]=='\n'){
			S[i]=0;
			s[++tot]=&S[i+1];
		}
	}
	tot--;
	for(i=1;i<=tot;i++){
		if(!strcmp(s[i],"add")){
			if(!strcmp(s[++i],"arrow")){
				float tx,tz,sx,sz,trot;
				int tid;
				tx=getfloat(i);
				tz=getfloat(i);
				sx=getfloat(i);
				sz=getfloat(i);
				trot=getfloat(i);
				tid=getint(i);
				int tbel=getint(i);
				p[n++]=new Arrow(tx,tz,sx,sz,trot,tbel,tid);
			}
		}
		else if(!strcmp(s[i],"del")){
			int tid=getint(i);
			Sd.insert(tid);
		}
		else if(!strcmp(s[i],"damage")){
			int tid=getint(i);
			int tdm=getint(i);
			int tfrm=getint(i);
			if(tid==id){
				ply[id]->hp-=tdm;
				chkdead(tfrm);
			}
		}
		else if(!strcmp(s[i],"CLOSE")){
			int t=getint(i);
			liv.erase(t);
			char tt[20];
			sprintf(tt,"%d",t);
		}
		else if(!strcmp(s[i],"kill")){
			int p1=getint(i);
			int p2=getint(i);
			sprintf(buf,"%d %d\n",p1,id);
			char tmp[110];
			sprintf(tmp,"%s killed %s",ply[p1]->nickname,ply[p2]->nickname);
			evtlist.add(tmp);
			if(p1==id){
				ply[p1]->exp++;
				ply[p1]->kil++;
			}
		}
		else{
			char nm[110];
			memset(nm,0,sizeof(nm));
			sscanf(s[i],"%s",nm);
			int t,thp,tkil;
			float tx,tz,trot;
			t=getint(i);
			tx=getfloat(i);
			tz=getfloat(i);
			trot=getfloat(i);
			thp=getint(i);
			tkil=getint(i);
			if(t==0){
				continue;
			}
			if(liv.find(t)==liv.end()){
				ply[t]=new Player(nm);
				liv.insert(t);
			}
			ply[t]->posx=tx;
			ply[t]->posz=tz;
			ply[t]->rot=trot;
			ply[t]->hp=thp;
			ply[t]->kil=tkil;
		}
	}
}
void Move(){
	Show::nowt=clock();
	float tx=Entity_3d::camx,tz=Entity_3d::camz;
	if(down['W']){
		Entity_3d::camz+=(Show::nowt-lst)*3.f/1000;
	}
	if(down['S']){
		Entity_3d::camz-=(Show::nowt-lst)*3.f/1000;
	}
	if(down['A']){
		Entity_3d::camx-=(Show::nowt-lst)*3.f/1000;
	}
	if(down['D']){
		Entity_3d::camx+=(Show::nowt-lst)*3.f/1000;
	}
	if(mp[(int)Entity_3d::camx][(int)Entity_3d::camz]=='#'){
		Entity_3d::camx=tx;
		Entity_3d::camz=tz;
	}
}
void Refresh(){
	int i;
	set<int>::iterator it;
	for(i=0;i<n;i++){
		if((it=Sd.find(p[i]->eid))!=Sd.end()){
			Sd.erase(it);
			swap(p[i],p[n-1]);
			i--;
			n--;
			delete p[n];
		}
		else{
			p[i]->Refresh();
			if(p[i]->typ=="arrow"){
				Arrow* P=(Arrow*)p[i];
				//*
				if(p[i]->posx<1||p[i]->posx>30||p[i]->posz<1||p[i]->posz>30){
					swap(p[i],p[n-1]);
					i--;
					n--;
					delete p[n];
					continue;
				}
				if(P->bel!=id&&sqr(p[i]->posx-Entity_3d::camx)+sqr(p[i]->posz-Entity_3d::camz)<1){
					sprintf(buf,"del %d",p[i]->eid);
					tcp.add(buf);
					ply[id]->hp--;
					chkdead(P->bel);
					continue;
				}
				if(mp[(int)p[i]->posx][(int)p[i]->posz]=='#'){
					swap(p[i],p[n-1]);
					i--;
					n--;
					delete p[n];
					continue;
				}
			}
		}
	}
	Move();
	if(ply[id]->exp>ply[id]->lev){
		ply[id]->lev++;
		ply[id]->hp++;
		ply[id]->exp=0;
	}
	ranklist.clr();
	for(it=liv.begin();it!=liv.end();it++){;
		ranklist.add(ply[*it]->nickname,ply[*it]->kil,*it);
	}
	lst=clock();
}
void Release(){
	DX::Device->Release();
	DX::d3d9->Release();
}
void RenderStart(){
	Show::Device->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(255,255,255),1.0f,0);
	Show::Device->BeginScene();
	char tmp[110];
	sprintf(tmp,"Please enter your name and press ENTER\n%s",nickname);
	TXT::Render(tmp,DT_CENTER|DT_VCENTER,D3DCOLOR_XRGB(0,0,0),25,15);
	Show::Device->EndScene();
	Show::Device->Present(NULL,NULL,NULL,NULL);
}
INT WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,INT){
	srand((unsigned int)time(NULL));
	WNDCLASSEX wc={sizeof(WNDCLASSEX),CS_CLASSDC,WndProc,0L,0L,GetModuleHandle(NULL), NULL, NULL, NULL, NULL,TEXT("client"),NULL };
	RegisterClassEx(&wc);
	HWND hWnd = CreateWindow(TEXT("client"),TEXT("client"),WS_OVERLAPPEDWINDOW,600,200,SCREEN_WIDTH,SCREEN_HEIGHT,GetDesktopWindow(),NULL,wc.hInstance,NULL);
	if(!DX::initD3d(hWnd)){
		MessageBox(0,"Init Direct3d Error","Error",0);
		return 0;
	}
	ShowWindow(hWnd,SW_SHOW);
	UpdateWindow(hWnd);
	MSG msg={0};
	for(;msg.message!=WM_QUIT;){
		POINT m_mouse;
		GetCursorPos(&m_mouse);
		ScreenToClient(hWnd,&m_mouse);
		Show::Mousex=(float)m_mouse.x-SCREEN_WIDTH/2+10;
		Show::Mousey=(float)m_mouse.y-SCREEN_HEIGHT/2+15;
		rot=atan2(Show::Mousey,Show::Mousex);
		while(PeekMessage(&msg,NULL,0U,0U,PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if(gamestat==0){
			RenderStart();
		}
		if(gamestat==1){
			Refresh();
			Communicate();
			Render();
		}
	}
	Release();
	return 0;
}
