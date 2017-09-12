#pragma once
#include<WinSock2.h>
#include<cstdio>
const int BufLen = 1024;

class TCPtransport{
public:
	TCPtransport(void);
	~TCPtransport(void);
	void init(char *ipadr,int port);
	char SendBuf[BufLen];
	char GetBuf[BufLen];
	char Buf[BufLen];
	void add(char *s);
	void clr();
	void send(char *nickname,int id,float x,float z,float rot);
	void recv();
	int LEN;
private:
	int wzh;
	WSADATA wsd;
	long int Addr;
	int Port;
	SOCKET tcp_socket;
	SOCKADDR_IN tcpAddr;
};
