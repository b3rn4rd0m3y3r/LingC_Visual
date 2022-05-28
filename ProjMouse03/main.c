#include <windows.h>
#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))

HWND staticTextField1, staticTextField2, editTotal;
HDC hdcStatic;
int Linha, Coluna, xPos, yPos;
POINT ponto;
/* 
	Descrição dos parâmetros
	 
	WPARAM wParam // Handle to a display context (DC).
	LPARAM lParam; // Handle to a child window (control).
*/
	static COLORREF redColor = RGB(255,0,0);
	static COLORREF blueColor = RGB(0,0,255);
	static COLORREF greenColor = RGB(0,255,0);
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
   	PAINTSTRUCT ps;
   	HDC hdc;
   	char greeting[] = "Hello, Windows desktop!";
	HINSTANCE g_inst;
	hdcStatic = (HDC)wParam;
	char str[255] ;
	int numero;
	int j = 0;
	HWND hWndControl = (HWND)lParam;



	switch(Message) {
	   	case WM_MOUSEMOVE:
	   		//hdc = GetDC(hwnd);
	 			xPos = LOWORD(lParam);
	 			yPos = HIWORD(lParam);
				sprintf(str,"Ponto %d %d", xPos, yPos);
				SendMessage(staticTextField1,WM_SETTEXT,(WPARAM)strlen(str),str);
				SendMessage(hwnd,WM_PAINT,xPos,yPos);
				//SetPixel(hdc, xPos, yPos,blueColor);
			//TextOut(hdc, 15, 150, str, strlen(str));
			//ReleaseDC(hwnd, hdc);
			break;
		case WM_PAINT:
	      	hdc = BeginPaint(hwnd, &ps);
			EndPaint(hwnd, &ps);
			//------------------------
	      	hdc = GetDC(hwnd);
			xPos = (int)wParam;
			yPos = (int)lParam;
	      	SetTextColor(hdc, RGB(255, 0, 0));
			TextOut(hdc, 15, 80, greeting, strlen(greeting));
			SetPixel(hdc, xPos, yPos,blueColor);
			ReleaseDC(hwnd, hdc);
	      	
	      	break;
			  		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
	    case WM_CREATE:
			Linha = 20;	Coluna = 20;	
	        staticTextField1 = CreateWindow("STATIC", "static1", WS_VISIBLE 
	         | WS_CHILD, Coluna, Linha, 150, 20, hwnd, NULL, NULL, NULL);
	        Coluna = 180;
	        staticTextField2 = CreateWindow("STATIC", "static2", WS_VISIBLE | 
	         WS_CHILD | WS_BORDER, Coluna, Linha, 150, 20, hwnd, NULL, NULL, NULL);
	        
			Linha = 100; Coluna = 20;
			editTotal = CreateWindowEx (WS_EX_CLIENTEDGE,"EDIT", "edit1",       
	        WS_VISIBLE | WS_CHILD, Coluna, Linha, 400, 50, hwnd, NULL, g_inst, NULL );	
	         
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
