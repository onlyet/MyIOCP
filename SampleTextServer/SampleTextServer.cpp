// SampleTextServer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "MyIOCP.h"


//MyIOCP myiocp;

int _tmain(int argc, _TCHAR* argv[])
{
	
	_CrtSetDbgFlag( _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG ) | _CRTDBG_LEAK_CHECK_DF );

    CBaseIOCPServer myiocp;
	myiocp.Startup(20000,1,10000);

	getchar();


	myiocp.Shutdown();

	_CrtDumpMemoryLeaks( );

	return 0;
}

