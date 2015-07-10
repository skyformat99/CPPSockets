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
#include "inet.h"
#include "DatagramPacket.h"
 

//  InputStream ( Java Naming style )
class InputStream
{
	friend class Socket;
	SOCKET m_s;
public:
   
	BYTE readByte();

	WORD  readWORD();

	DWORD readDWORD();

	float readFloat(); 

	int read(char* buff,int buffsize);
	
	//fixme
};

//  OutputStream ( Java Naming style )
class OutputStream
{
	friend class Socket;
	SOCKET m_s;
public:

 
	bool writeByte(BYTE b);
 
	bool writeWord(WORD word);

	bool writeDWORD(DWORD dw);

	bool writeFloat(float f);
 
	int write(const char* buff,int  size);
 
	//fixme
};

//  Socket ( Java Naming style )
class Socket	
{ 

protected:
	SOCKET m_s;


public:
	Socket()
	{
		SockInit::Instance();

		m_s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	};

	//     创建一个流套接字并将其连接到指定主机上的指定端口号。
	Socket(char* host, int port)
	{
		SockInit::Instance();

		m_s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		 
		connect(  SocketAddress(  InetAddress::getByName(host) ,port) ); 
	}

	virtual ~Socket()
	{
		
	};


	void  SetSock (  SOCKET  s)  {	m_s=s ; }

	SOCKET GetSock(){return m_s;}

	void close()
	{
		if(m_s!=INVALID_SOCKET)
		{
			closesocket(m_s);
			m_s=INVALID_SOCKET;
		}
	}

	//	返回此套接字的输入流。 
	InputStream getInputStream(){InputStream s;s.m_s=m_s;return s;}

	//	返回此套接字的输出流。 
	OutputStream getOutputStream(){OutputStream s;s.m_s=m_s;return s;}

	//将此套接字连接到服务器。 
	void connect(SocketAddress endpoint) 
	{ 

		SOCKADDR_IN server; 
		memset(&server, 0, sizeof(SOCKADDR_IN));
		server.sin_family = AF_INET;
		server.sin_addr.S_un.S_addr = inet_addr(endpoint.getIP());
		server.sin_port = htons(endpoint.getPort());

		int ret=::connect(m_s, (struct sockaddr *)&server, sizeof(SOCKADDR_IN));
		if (ret==SOCKET_ERROR)
		{
			exception e("connect exception!");
			throw  e;	
		}
		 

	}	  
 

};

 