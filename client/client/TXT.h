#pragma once
#include <d3dx9.h>
#include "Show.h"
class TXT:public Show
{
public:
	TXT();
	~TXT();
	static ID3DXFont* g_font;
	static void Render(char *txt);
	static void Render(char *txt,DWORD format);
	static void Render(char *txt,DWORD format,DWORD color);
	static void Render(char *txt,DWORD format,DWORD color,int h,unsigned int w);
	static bool inited;
};

