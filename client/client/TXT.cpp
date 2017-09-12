#include "TXT.h"

bool TXT::inited=0;
ID3DXFont* TXT::g_font;
TXT::TXT(){
	if(!inited){
		inited=1;
	}
}


TXT::~TXT()
{
}
void TXT::Render(char *txt){
	//*
	D3DXCreateFont(Device,20,10,20,0,FALSE,DEFAULT_CHARSET,0,0,0,"Arial",&g_font);
	g_font->DrawText(NULL,txt,(INT)strlen(txt),&g_client_rect,DT_TOP|DT_RIGHT,0xFFFFFF00);
	g_font->Release();
	//*/
}