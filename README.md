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
  
