

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

#include "socket.h"



BYTE ReadByte(SOCKET s)
{
	BYTE byte;
	int ret= recv( s, (char*)&byte, sizeof(BYTE) ,0 );
	if(ret!=sizeof(BYTE))
	{
		exception e("ReadByte exception!");
		throw  e;	
	}
	return byte;
}

WORD ReadWORD(SOCKET s)
{
	WORD w;
	int ret= recv( s, (char*)&w, sizeof(WORD) ,0 );
	if(ret!=sizeof(WORD))
	{
		exception e("ReadWORD exception!");
		throw  e;	
	}
	return w;
}

DWORD ReadDWORD(SOCKET s)
{
	DWORD dw;
	int ret= recv( s, (char*)&dw, sizeof(DWORD) ,0 );
	if(ret!=sizeof(DWORD))
	{
		exception e("ReadDWORD exception!");
		throw  e;	
	}
	return dw;
}

float ReadFloat(SOCKET s)
{
	float f;
	int ret= recv( s, (char*)&f, sizeof(float) ,0 );
	if(ret!=sizeof(float))
	{
		exception e("ReadFloat exception!");
		throw  e;	
	}
	return f;
}

 

bool SendByte(SOCKET s,BYTE byte)
{
	return  send(s, (char*)&byte, sizeof(BYTE) ,0);
}

bool SendWord(SOCKET s,WORD word)
{
	return send(s, (char*)&word, sizeof(WORD),0 );
}

bool SendDWORD(SOCKET s,DWORD dw)
{
	return send(s, (char*)&dw, sizeof(DWORD),0 );
}
bool SendFloat(SOCKET s,float f)
{
	return send(s, (char*)&f, sizeof(float),0 );
}

BYTE InputStream::readByte()
{
	return ::ReadByte( m_s );
}

WORD  InputStream::readWORD()
{
	return  ::ReadWORD( m_s );
}

DWORD  InputStream::readDWORD()
{
	return   ::ReadDWORD( m_s );
}

float  InputStream::readFloat()
{
	return  ::ReadFloat( m_s );
}



int  InputStream::read(char* buff,int buffsize)
{
	return recv(m_s,buff,buffsize,0);
}
  


bool OutputStream::writeByte(BYTE byte)
{
	return  SendByte( m_s ,byte );
}
 
bool OutputStream::writeWord(WORD word)
{
	return  SendWord(m_s, word );
}

bool  OutputStream::writeDWORD(DWORD dw)
{
	return SendDWORD(m_s,  dw );
}
bool  OutputStream::writeFloat(float f)
{
	return  SendFloat(m_s, f );
}
 
int OutputStream::write(const char* buff,int  size)
{
	return send(m_s,buff,size,0);
}
 