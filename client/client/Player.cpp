#include "Player.h"
#include<cstdio>
bool Player::inited=0;
MOD Player::mod;
D3DMATERIAL9 Player::mtrlfont;
Player::Player(){
	memset(nickname,0,sizeof(nickname));
	sprintf(nickname,"unnamed");
	init();
}
Player::~Player(){
	TextMesh->Release();
}
void Player::init(){

	if(inited){
		return ;
	}
	inited=1;
	mod.init("wyr.x");
	ZeroMemory(&mtrlfont,sizeof(D3DMATERIAL9));
	//漫反射光  
	mtrlfont.Diffuse.r  = 1.0f;
	mtrlfont.Diffuse.g  = 0.0f;
	mtrlfont.Diffuse.b  = 0.0f;
	mtrlfont.Diffuse.a  = 1.0f;
	//环境光
	mtrlfont.Ambient.r = 1.f;
	mtrlfont.Ambient.g = 0.f;
	mtrlfont.Ambient.b = 0.0f;
	mtrlfont.Ambient.a = 1.0f;
	//镜面反射光  
	mtrlfont.Specular.r = 1.0f;
	mtrlfont.Specular.g = 1.0f;
	mtrlfont.Specular.b = 1.0f;
	mtrlfont.Specular.a = 1.0f;
	mtrlfont.Power = 25.0f;

}
Player::Player(char *nm){
	init();
	int i;
	kil=0;
	weapon=2;
	skill1=skill2=0;
	memset(nickname,0,sizeof(nickname));
	for(i=0;nm[i];i++){
		nickname[i]=nm[i];
	}
	hp=1;
	exp=0;
	lev=1;
	HDC hdc = CreateCompatibleDC(NULL);
	HFONT hFont = CreateFont(0,0,0,0,FW_BOLD,false,false,false,
		DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Arial");
	SelectObject(hdc,hFont);
	D3DXCreateText(Device,hdc,nickname,0.001f,0.05f,&TextMesh,NULL,NULL);
	DeleteObject(hFont);
	DeleteDC(hdc);
}
void Player::Render(){

	preSet();

	mod.Render();

	hps.hp=hp*.25;
	hps.posx=posx;
	hps.posz=posz;

	hps.Render();

	posy=3;
	float trot=rot;
	rot=0;
	posx-=strlen(nickname)*.23;
	rotx=0.7853975;
	Device->SetMaterial(&mtrlfont);
	preSet();

	Device->LightEnable(0,FALSE);
	Device->SetRenderState(D3DRS_AMBIENT,D3DCOLOR_XRGB(255,255,255));
	TextMesh->DrawSubset(0);
	posx+=strlen(nickname)*.23;
	rotx=0;
	rot=trot;
	posy=0;

}