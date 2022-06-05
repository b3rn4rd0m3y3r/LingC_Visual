#include <windows.h>
#pragma comment(lib, "user32.lib")
	
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	char *buffer;
	
	SYSTEM_INFO siSysInfo;
	GetSystemInfo(&siSysInfo); 
	
	char cpu[100],noProc[100], wmajor[100], wminor[100], versao[100];
	// Informações Windows
     char lszValue[255];
     TCHAR lszValue1[255] = {};
     DWORD BufferSize = sizeof(lszValue);
     DWORD regval = 0;
     HKEY hKey;
     LONG returnStatus;
     //DWORD dwType=REG_SZ;
     //DWORD dwType1=REG_DWORD;
     DWORD dwSize=255;
     
    // INICIO - Read ipsis literis
    unsigned long type=REG_DWORD, size=1024;
    DWORD bufferlong;
    // FIM - Para o read versão bufferlong - ipsis literis
    
	// GetVersion - INICIO
    DWORD dwVersion = 0; 
    DWORD dwMajorVersion = 0;
    DWORD dwMinorVersion = 0; 
    DWORD dwBuild = 0;

    dwVersion = GetVersion();
 
    // Explode Major and minor

    dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
    dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));
	// FIM
     returnStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", NULL,  KEY_ALL_ACCESS, &hKey);
     if (returnStatus == ERROR_SUCCESS){
          returnStatus = RegQueryValueEx(hKey, TEXT("DisplayVersion"), NULL, NULL, (LPBYTE) &lszValue, &dwSize);
          if (returnStatus == ERROR_SUCCESS){
				sprintf(wmajor,"Versao Windows: %s ",lszValue);
          	} else {
			  	sprintf(wmajor,"Versao Windows: %s ","N/A");
			}
			// Versão ipsis literis
			returnStatus = RegQueryValueEx(hKey,"CurrentMajorVersionNumber",NULL,&type,(LPBYTE)&bufferlong,&size);
    		dwMajorVersion = (DWORD)(LOBYTE(bufferlong));
    		dwMinorVersion = (DWORD)(HIBYTE(bufferlong));
    		// FIM - Versão ipsis literis
		  //returnStatus = RegQueryValueExA(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\"), "CurrentBuildNumber",  NULL, &lszValue1, &BufferSize);
          //returnStatus = RegGetValue(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\"), _T("CurrentBuildNumber"), RRF_RT_REG_SZ, NULL, &lszValue1, &BufferSize);
               	
				sprintf(versao,"Numero Windows: %lu ", dwMajorVersion);
               	sprintf(wminor,"Numero Windows: %lu ", dwMinorVersion);
		
       	}
  	RegCloseKey(hKey);

     
	// FIM
	sprintf(cpu,"CPU: %d",siSysInfo.dwProcessorType);
	sprintf(noProc,"No.Proc: %d",siSysInfo.dwNumberOfProcessors);
	
	
	HWND dsktp;
	char greeting[] = "Hello, Windows desktop!";
	
	PAINTSTRUCT ps;
	HDC hdc;   	
	HINSTANCE g_inst;
	int len;
	switch(Message) {
	   	case WM_PAINT:
	      	//dsktp = GetDesktopWindow();
			//hdc = GetDC(dsktp);         
			hdc = BeginPaint(hwnd, &ps);
	      	// Aqui Ã© ordenada a apresentaÃ§Ã£o da tela
	      	SetTextColor(hdc, RGB(0, 0, 0));
			TextOut(hdc, 400, 300, cpu, strlen(cpu));
			TextOut(hdc, 400, 330, noProc, strlen(noProc));
			TextOut(hdc, 400, 360, wmajor, strlen(wmajor));
			TextOut(hdc, 400, 390, versao, strlen(versao));
			TextOut(hdc, 400, 420, wminor, strlen(wminor));
			
	      	// Fim da apresentaÃ§Ã£o
	      	EndPaint(hwnd, &ps);
	      	
	      	break;		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Minha Tela",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		1080, /* width */
		758, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
