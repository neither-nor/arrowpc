#include "Ranklist.h"
#include "TXT.h"


Ranklist::Ranklist()
{
}


Ranklist::~Ranklist()
{
}

void Ranklist::Render(){
	sort(rk+1,rk+cnt+1);
	memset(rklist,0,sizeof(rklist));
	char *trk=rklist;
	sprintf(trk,"ÅÅĞĞ°ñ      \n");
	while(*trk){
		trk++;
	}
	int i;
	for(i=1;i<=cnt;i++){
		sprintf(trk,"%d %s %d\n",i,rk[i].name,rk[i].kil);
		while(*trk){
			trk++;
		}
	}
	TXT::Render(rklist,DT_TOP|DT_RIGHT,D3DCOLOR_XRGB(0,0,0));
}
void Ranklist::add(char *nam,int kil,int id){
	cnt++;
	sprintf(rk[cnt].name,"%s",nam);
	rk[cnt].kil=kil;
	rk[id].id=id;
}
void Ranklist::clr(){
	cnt=0;
}