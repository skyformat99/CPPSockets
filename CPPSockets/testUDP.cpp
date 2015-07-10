//
///* 
//===============================================================================
//The MIT License
//
//
//Copyright (C) 1994-2015 simawei<simawei@qq.com>
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//THE SOFTWARE.
//
//===============================================================================
//*/
//
//
//
//#include "DatagramSocket.h"
//
////-------------------------------------------------------------------------------------------------
//// Main
////-------------------------------------------------------------------------------------------------
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	try
//	{
//
//		//udp socket bind on 444 port
//		DatagramSocket  u(444);
//		
//		//sendto target 444 port
//		std::string s1="hello myself!";
//		DatagramPacket spk( s1.c_str(),s1.length() , SocketAddress("127.0.0.1",444)   ); 
//		u.send(spk);
//
//		while (1)
//		{
// 
//				//receive  udp Packet
//				DatagramPacket pk ;
//				u.receive(pk);
//				printf("recv len[%d] %s \n",pk.getLength(),pk.getData());
//
//				//Sleep(1);
//
//				//echo self
//				DatagramPacket spk( pk.getData(), pk.getLength(),   pk.getSocketAddress() );
//				u.send(spk);
//
//			  
//		}
//
//	}
//	catch (exception  e)
//	{
//		printf("err %s",e.what());
//	}
//	return 0;
//}
//
