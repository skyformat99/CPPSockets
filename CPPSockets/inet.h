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

#include <WINSOCK2.H>
#include <Mswsock.h>

#include <Windows.h>

#include <stdio.h>
#include <iostream>
#include <tchar.h>


class SocketAddress;


 //  InetAddress ( Java Naming style )
class InetAddress
{
	friend class SocketAddress;
 
	static unsigned long   HostToNetAddr(const char *host)
	{
		long i;
		struct hostent *he;

		if((i=inet_addr(host))<0)
			if((he=gethostbyname(host))==NULL)
				return(0);
			else
				return(*(unsigned long *)he->h_addr);

		return(i);
	}

protected:
	in_addr m_addr; 


public:


	//�ڸ���ԭʼ IP ��ַ������£����� InetAddress ���󡣲����������ֽ�˳�򣺵�ַ�ĸ�λ�ֽ�λ�� getAddress()[0] ��
	//addr - �����ֽ�˳���ԭʼ IP ��ַ 
	static InetAddress getByAddress(char* ip) //throws UnknownHostException
	{

		InetAddress i;
		i.m_addr.s_addr= inet_addr(ip);
		return i;
	};


	// �ڸ����������������ȷ�������� IP ��ַ�� ����->ip
	static InetAddress getByName(char* host) //throws UnknownHostException
	{

		InetAddress i;
		i.m_addr.s_addr= HostToNetAddr(host);
		return i;
	};


};

//  SocketAddress ( Java Naming style )
class  SocketAddress
{
	friend class DatagramPacket;
	friend class DatagramSocket;

	sockaddr_in m_addr; 

public:
	SocketAddress( ) {  }

	//���� IP ��ַ�Ͷ˿ںŴ����׽��ֵ�ַ�� 
	SocketAddress(InetAddress addr, int port) {

		m_addr.sin_family = AF_INET;
		m_addr.sin_addr.s_addr = addr.m_addr.s_addr;
		m_addr.sin_port = htons( port );

	}

	//�����������Ͷ˿ںŴ����׽��ֵ�ַ�� 
	SocketAddress(char* hostname, int port){
		m_addr.sin_family = AF_INET;
		m_addr.sin_addr.s_addr =  InetAddress::HostToNetAddr(hostname);
		m_addr.sin_port = htons( port );
	}

	//	��ȡ InetAddress�� 
	InetAddress getAddress() 
	{
		return InetAddress::getByAddress(getIP());
	}

	char* getIP()  
	{
		return  inet_ntoa(m_addr.sin_addr);
	}

	//	��ȡ�˿ںš�
	int getPort() 
	{
		return ntohs(m_addr.sin_port);
	}

};
