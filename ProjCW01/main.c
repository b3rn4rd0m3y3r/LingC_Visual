#include <windows.h>


/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	HWND staticTextField1, staticTextField2;
	HDC hdcStatic = (HDC)wParam;
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
	    case WM_CREATE:
			
	         staticTextField1 = CreateWindow("STATIC", "static1", WS_VISIBLE 
	         | WS_CHILD, 20, 20, 300, 25, hwnd, NULL, NULL, NULL);
	
	
	         staticTextField2 = CreateWindow("STATIC", "static2", WS_VISIBLE | 
	         WS_CHILD | WS_BORDER, 20, 200, 300, 20, hwnd, NULL, NULL, NULL);
	         
	         //SetTextColor((HDC)staticTextField1, RGB(255, 0, 0));
			
			
	         break;	
			case WM_CTLCOLORSTATIC:
				
        		SetTextColor(hdcStatic, RGB(255,255,255));
				//SetTextColor( (HDC)staticTextField1, RGB(255,0,0) );
				break;	
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
	wc.hIcon		 = LoadIcon(hInstance, "A"); /* Use hInstance como referência do local do icone */
	wc.hIconSm		 = LoadIcon(hInstance, "A"); /* use o nome "A" para usar o ícone do projeto */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Minha Janela",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		640, /* width */
		480, /* height */
		NULL,NULL,hInstance,NULL);
		
		SetWindowText(hwnd, "Novo nome da janela");
		
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
