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
	static bool inited;
};

