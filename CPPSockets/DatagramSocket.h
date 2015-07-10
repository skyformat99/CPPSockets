/* 
===============================================================================
The MIT License


Copyright (C) 1994-2015 simawei<simawei@qq.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

===============================================================================
*/


#pragma once

#include "SockInit.h"
#include "DatagramPacket.h"


 //  DatagramSocket ( Java Naming style )
class DatagramSocket
{
	SOCKET s;
public:
	//�������ݱ��׽��ֲ�����󶨵������������κο��õĶ˿ڡ�
	//DatagramSocket(void)
 

	//�������ݱ��׽��ֲ�����󶨵����������ϵ�ָ���˿ڡ�
	DatagramSocket(int port=0)
	{
		SockInit::Instance();

		s=socket(AF_INET,SOCK_DGRAM,0);
		if(INVALID_SOCKET==s)
		{ 
			exception e("socket create exception!");
			throw  e;	 
		}
 
		BOOL bNewBehavior = FALSE;
		DWORD dwBytesReturned = 0;
		WSAIoctl(s, SIO_UDP_CONNRESET, &bNewBehavior, sizeof bNewBehavior, NULL, 0, &dwBytesReturned, NULL, NULL);

		SOCKADDR_IN addrSock;
		addrSock.sin_family=AF_INET;
		addrSock.sin_port=htons(port);
		addrSock.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
		int  ret=bind(s,(SOCKADDR*)&addrSock,sizeof(SOCKADDR));
		if(SOCKET_ERROR==ret)
		{
			closesocket(s); 
			exception e("bind  exception!");
			throw  e;	 

		} 
	}
		 
	//�������ݱ��׽��֣�����󶨵�ָ���ı��ص�ַ��
	DatagramSocket(int port, InetAddress laddr) ;
	
	//�������ݱ��׽��֣�����󶨵�ָ���ı����׽��ֵ�ַ��
	DatagramSocket(SocketAddress bindaddr) ;
 

	~DatagramSocket(void){
		closesocket(s);
	}

	//�Ӵ��׽��ֽ������ݱ����� 
	void receive(DatagramPacket& p) 
	{
		int len=sizeof(SOCKADDR_IN); 
		int  ret=recvfrom(s,p.getData(), p.getLength() ,0,(SOCKADDR*)& p.addr.m_addr,&len);
		if(SOCKET_ERROR==ret)
		 { 
			 //printf("err %d\n",WSAGetLastError());
			 exception e("recvfrom  exception!");
			 throw  e;	 
		 }

		p.len=ret; 

	}
		 
	
	//�Ӵ��׽��ַ������ݱ����� 
	void send(DatagramPacket& p)
	{	
		int ret=sendto(s,  p.getData() ,  p.getLength() , 0, (const sockaddr *)& p.addr.m_addr, sizeof(SOCKADDR_IN) );
		if (ret==SOCKET_ERROR )
		{
			//printf("err %d\n",WSAGetLastError());
			exception e("sendto  exception!");
			throw  e;	 
		}
	}
	 

};

 