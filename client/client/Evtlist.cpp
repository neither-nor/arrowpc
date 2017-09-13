#include "Evtlist.h"
#include "TXT.h"


Evtlist::Evtlist(){
	evthd=evttl=1;
}


Evtlist::~Evtlist()
{
}

void Evtlist::add(char *evt){
	evtq[(evttl%=1000)++]=Evt(evt,clock());
}

void Evtlist::Render(){
	while(evthd!=evttl&&evtq[evthd].tim<clock()-4000){
		(evthd%=1000)++;
	}
	memset(evnts,0,sizeof(evnts));
	int i;
	char *tevt=evnts;
	for(i=evthd;i!=evttl;(i%=1000)++){
		sprintf(tevt,"%s\n",evtq[i].des);
		while(*tevt){
			tevt++;
		}
	}
	TXT::Render(evnts,DT_TOP|DT_LEFT,D3DCOLOR_XRGB(255,0,0));
}