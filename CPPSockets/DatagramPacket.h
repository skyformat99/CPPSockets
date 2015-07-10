/* 
===============================================================================
The MIT License


Copyright (C) 1994-2015  simawei<simawei@qq.com>

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


#include "inet.h"
 

#define  DATALEN 1024*20


 //  DatagramPacket ( Java Naming style )
class DatagramPacket
{
	friend class DatagramSocket;

	char data[DATALEN];
	int len;

	SocketAddress addr;

public:
	 
	//构造 DatagramPacket，用来接收长度20k以内   的数据包
	DatagramPacket(void) 
	{
		memset(data,0,DATALEN);
		len=DATALEN;
	};
		 
	//构造数据报包，用来将长度为 length 的包发送到指定主机上的指定端口号。 
	DatagramPacket(const char* buf, int length, InetAddress address, int port):addr(address,  port)
	{
		memcpy(data,buf,length);
		len=length;	
	}
 
	//构造数据报包，用来将长度为 length 的包发送到指定主机上的指定端口号。 
	DatagramPacket(const char* buf, int length, SocketAddress address) 
	{
		memcpy(data,buf,length);
		len=length;	
		addr=address;
	}
		 
	char* getData() 
	//	返回数据缓冲区。
	{
		return data;
	}

	int getLength() 
		//返回将要发送或接收到的数据的长度。 
	{
		return len;
	}

	int getPort() 
	//	返回某台远程主机的端口号，此数据报将要发往该主机或者是从该主机接收到的。 
	{
		ntohs(addr.m_addr.sin_port);
	}
	
	SocketAddress getSocketAddress() 
	//	获取要将此包发送到的或发出此数据报的远程主机的 SocketAddress（通常为 IP 地址 + 端口号）。 
	{
		return addr;
	}

	~DatagramPacket() 
	{
		 
	}
};


 