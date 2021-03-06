#include <windows.h>
#include <stdio.h>

HWND staticTextField1;
UINT Message_ant = 0;
int noMsg = 0;
/* 
	Descrição dos parâmetros
	 
	WPARAM wParam // Handle to a display context (DC).
	LPARAM lParam; // Handle to a child window (control).
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
	
   	PAINTSTRUCT ps;
   	HDC hdc;
   	char greeting[] = "Hello, Windows desktop!";
   	char txtMessage[40];
	HINSTANCE g_inst;
	HDC hdcStatic = (HDC)wParam;
	char str[255] = "";
	int j = 0;
	HWND hWndControl = (HWND)lParam;
	FILE *fp;
	
	
	
	
	noMsg++;
	switch(Message) {

	   	case WM_PARENTNOTIFY:
	   		strcpy(txtMessage,"WM_PARENTNOTIFY");
			break;
	   	case WM_SHOWWINDOW:
	   		strcpy(txtMessage,"WM_SHOWWINDOW");
			break;
	   	case WM_ACTIVATEAPP:
	   		strcpy(txtMessage,"WM_ACTIVATEAPP");
			break;
	   	case WM_NCACTIVATE:
	   		strcpy(txtMessage,"WM_NCACTIVATE");
			break;
		case WM_PAINT:
	      	//if( Message != Message_ant){
			  strcpy(txtMessage,"WM_PAINT");
			  //}
			  
			/*
			hdc = BeginPaint(hwnd, &ps);
	      	// Here your application is laid out.
	      	// For this introduction, we just print out "Hello, Windows desktop!"
	      	// in the top left corner.
	      	SetTextColor(hdc, RGB(255, 0, 0));
			TextOut(hdc, 15, 80, greeting, strlen(greeting));
	      	
	      	// End application-specific layout section.
	
	      	EndPaint(hwnd, &ps);
	      	*/
	      	break;
			  		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: 
			strcpy(txtMessage,"WM_DESTROY");
			PostQuitMessage(0);
			break;
		
	    case WM_CREATE:
			strcpy(txtMessage,"WM_CREATE");
	        staticTextField1 = CreateWindow("STATIC", "static1", WS_VISIBLE 
	         | WS_CHILD, 20, 20, 300, 25, hwnd, NULL, NULL, NULL);
	         
			hdcStatic = GetDC(staticTextField1);
			SetTextColor(hdcStatic, RGB(255, 0, 0));
	         
	        break;	
		case WM_CTLCOLORSTATIC:
			strcpy(txtMessage,"WM_CTLCOLORSTATIC");
			if(staticTextField1 == hWndControl){
				hdcStatic = GetDC(hWndControl);
				SetTextColor(hdcStatic, RGB(255, 0, 0));
				SetBkMode(hdcStatic, TRANSPARENT);
				}
			
			break;	
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			/*
			if( Message != Message_ant){
				Message_ant = Message;
				noMsg = 0;				
				}
			*/
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	if( Message != Message_ant){
		fp = fopen("log.txt","a");
		fprintf(fp,"%s (%d)\n",txtMessage,noMsg);
		fclose(fp);
		Message_ant = Message;
		noMsg = 0;
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
