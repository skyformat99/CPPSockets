# CPPSockets


CPPSockets 是一个 C++ 编写的网络类库,采用 Java 的类命名方式和接口,仿造了一个 C++版本的,比如ServerSocket DatagramSocket SocketAddress


				CPPSockets README

CPPSockets is a framework library written in C++.
CPPSockets provide simple, common-sense API to networking. 
it provide socket classes such as  ServerSocket DatagramSocket SocketAddress,  Java Naming style  .


If you update/fix some source code ,please send me a copy  . thanks . 

			

Enjoy!

 
				-- simawei <simawei@qq.com>
 

You can get the source code from my home page:

	http://code.qtuba.com/studio/CPPSockets.html




here is the tcp  sample :

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
 





here is the udp  sample :

try
	{

		//udp socket bind on 444 port
		DatagramSocket  u(444);
		
		//sendto target 444 port
		std::string s1="hello myself!";
		DatagramPacket spk( s1.c_str(),s1.length() , SocketAddress("127.0.0.1",444)   ); 
		u.send(spk);

		while (1)
		{

				//receive  udp Packet
				DatagramPacket pk ;
				u.receive(pk);
				printf("recv len[%d] %s \n",pk.getLength(),pk.getData());

				//Sleep(1);

				//echo self
				DatagramPacket spk( pk.getData(), pk.getLength(),   pk.getSocketAddress() );
				u.send(spk);

			  
		}

	}
	catch (exception  e)
	{
		printf("err %s",e.what());
	}




  
