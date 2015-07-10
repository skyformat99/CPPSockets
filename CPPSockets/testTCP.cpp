
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
 
 
#include "serversocket.h"
#include <sstream>

DWORD WINAPI clientthread(LPVOID l)
{
	Socket b=*(Socket*)l;


	std::stringstream   content;
	content<<"hello, CPPSockets!<br> Java Naming style Sockets Classes";

	{
		std::stringstream Response;

		Response << "HTTP/1.1 " << 200   <<"\r\n"  ;

		Response << "Content-Type: text/html;charset=gb2312\r\n";

		if(content.str().length()>0)	
			Response<< "Content-Length: " << content.str().length()   << "\r\n";

		Response<< "Connection: close\n\n";

		b.getOutputStream().write( (char*)Response.str().c_str() ,Response.str().length() );

		if(content.str().length()>0)	
			b.getOutputStream().write( (char*)content.str().c_str() ,content.str().length()  );	

	}


	while ( 1 )
	{
		try
		{ 
  
			printf("%c",  b.getInputStream().readByte()   );
		
			//b.close();
		}catch(...)
		{
			printf("recv err [%d] \n",b.GetSock()); 
			b.close();
			break;
		}


	}

	printf("close [%d] \n",b.GetSock());

	return 0;
}

//-------------------------------------------------------------------------------------------------
// Main
//-------------------------------------------------------------------------------------------------

int _tmain(int argc, _TCHAR* argv[])
{	
  
	try
	{	
		//You can use the browser ( IE, Firefox, etc. ) to visit:

		//http://127.0.0.1/
		// simple http server 
		ServerSocket s(80);
		//or
		//ServerSocket s;
		//s.bind( SocketAddress("0.0.0.0",80));
	  
		printf("listen ok\n");
		
		Socket c2("127.0.0.1",80);
		while(1)
		{
			 
				Socket c = s.accept (); 
				printf(" Accept [%d]\n",c.GetSock() ); 
				CloseHandle( CreateThread(0,0,clientthread,&c,0,0)  );//fixme

		}

	}catch(exception e){
		printf("%s",e.what());
	}


}
 