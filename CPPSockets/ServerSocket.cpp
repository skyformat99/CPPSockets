
/* 
===============================================================================
The MIT License


Copyright (C) 1994-2015 simawei@qq.com

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

#include "serversocket.h"

ServerSocket::ServerSocket(void) 
{
	 
	
	
}

ServerSocket::ServerSocket(int port) 
{  
 
	bind(SocketAddress("0.0.0.0",port));
}

ServerSocket::~ServerSocket(void) 
{
	close();  
}

 

void ServerSocket::bind(SocketAddress endpoint )
{
 
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(endpoint.getPort());
	sin.sin_addr.S_un.S_addr = inet_addr(endpoint.getIP());
	// 绑定套节字到本地机器
	if(::bind(m_s, (sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR)
	{ 
		exception e("bind exception!");
		throw  e;	
	}
	// 进入监听模式
	::listen(m_s, 5);

	 
	 
}
 
Socket  ServerSocket::accept ()
{
	Socket client;
	 
	SOCKADDR_IN m_addr; 
	int nAddrLen = sizeof(SOCKADDR_IN);
	SOCKET c=  ::accept( m_s, (SOCKADDR*)&m_addr, &nAddrLen);

	if (c==INVALID_SOCKET)
	{
		//printf("%d \n",::WSAGetLastError());
		exception e("accept exception!");
		throw  e;	
	}
	  
	client.SetSock(c);
	return client;
}

 