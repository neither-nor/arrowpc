#include "TCPtransport.h"

TCPtransport::TCPtransport(void)
{
	LEN=0;
	clr();
}


TCPtransport::~TCPtransport(void)
{
	closesocket(tcp_socket);
	WSACleanup();
}

void TCPtransport::init(char *ipadr,int port){
	Addr = inet_addr(ipadr);
	Port = port;
	WSAStartup(MAKEWORD(2, 2), &wsd);
	tcp_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	tcpAddr.sin_family = AF_INET;
	tcpAddr.sin_port = htons(Port);
	tcpAddr.sin_addr.s_addr = Addr;

	connect(tcp_socket, (LPSOCKADDR)&tcpAddr, sizeof(tcpAddr));
}
void TCPtransport::add(char *s){
	int i;
	for(i=0;s[i];i++){
		Buf[wzh++]=s[i];
	}
	Buf[wzh++]='\n';
	Buf[wzh]=0;
}
void TCPtransport::clr(){
	wzh=0;
	ZeroMemory(Buf, BufLen);
	ZeroMemory(SendBuf,BufLen);
}

void TCPtransport::send(char *nickname,int id,float x,float z,float rot,int hp,int kil){
	sprintf(SendBuf,"%s %d %f %f %f %d %d\n%s",nickname,id,x,z,rot,hp,kil,Buf);
	LEN=max(LEN,strlen(SendBuf));
	::send(tcp_socket, SendBuf, BufLen, 0);
	clr();
}

void TCPtransport::recv(){
	::recv(tcp_socket, GetBuf, BufLen, 0);
	LEN=max(LEN,strlen(GetBuf));
}