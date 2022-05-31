#include <windows.h>
#define ID_BUTTON1 100
#define ID_BUTTON2 101
#define IDM_FILE_NEW 201
#define IDM_FILE_OPEN 202

HWND staticTextField1, staticTextField2, button1, button2, editTotal, edit2;
HMENU hMenu, hMenubar;
BOOL AddMenu;
/* 
	Descrição dos parâmetros
	 
	WPARAM wParam // Handle to a display context (DC).
	LPARAM lParam; // Handle to a child window (control).
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
	char * buffer;

   	PAINTSTRUCT ps;
   	HDC hdc;
   	char greeting[] = "Exemplo de botoes e de menu!";
	HINSTANCE g_inst;
	int len;
	HDC hdcStatic = (HDC)wParam;
	wchar_t wtext[20];
	char edittxt[255]={'\0'};
	int j = 0;
	HWND hWndControl = (HWND)lParam;

	switch(Message) {
		case WM_COMMAND:
			/*
				Botões
			*/

			switch (LOWORD(wParam)){
				
		        case ID_BUTTON1:
		          	// qual botão?
		            MessageBox(hwnd, "Vou copiar edit1 no edit2", "Copia", MB_OK | MB_ICONINFORMATION);
		            len = GetWindowTextLength(editTotal);
		            buffer = (char *)GlobalAlloc(GPTR, len + 1);
					SendMessage(editTotal,WM_GETTEXT,(WPARAM)len + 1, (LPARAM)buffer);
					//sprintf(edittxt,"%s",len,buffer);
					memcpy(edittxt, buffer, len);
					SendMessage(edit2, WM_SETTEXT, (WPARAM)len,(LPARAM)buffer); 
					MessageBox(hwnd, (LPCSTR)edittxt, "Tem", MB_OK | MB_ICONINFORMATION);

		          	break;				
		        case ID_BUTTON2:
		          	// qual botão?
		            MessageBox(hwnd, "Botao 2 foi clicado / WM_COMMAND", "Tem", MB_OK | MB_ICONINFORMATION);
		            //return 0;
		          	break;
				case IDM_FILE_NEW:
					MessageBox(hwnd, "File new", "Menu", MB_OK | MB_ICONINFORMATION);
					break;				
				}

			break;

	   	case WM_PAINT:
	      	hdc = BeginPaint(hwnd, &ps);
	      	SetTextColor(hdc, RGB(255, 0, 0));
			TextOut(hdc, 15, 50, greeting, strlen(greeting));
	      	EndPaint(hwnd, &ps);
	      	break;
			  		
		/* Fecha aplicação */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
	    case WM_CREATE:

hMenubar = CreateMenu();
hMenu = CreateMenu();

AppendMenuW(hMenu, MF_STRING, IDM_FILE_NEW, L"&New");
AppendMenuW(hMenu, MF_STRING, IDM_FILE_OPEN, L"&Open");
AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&File");

SetMenu(hwnd, hMenubar);
//InsertMenuW(hMenubar, 0, MF_BYPOSITION | MF_STRING, MF_POPUP, L"ItemA");

	        staticTextField1 = CreateWindow("STATIC", "static1", WS_VISIBLE 
	         | WS_CHILD, 20, 20, 300, 25, hwnd, NULL, NULL, NULL);
			hdcStatic = GetDC(staticTextField1);
			SetTextColor(hdcStatic, RGB(255, 0, 0));

	        button1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Copia Edits", WS_VISIBLE|WS_CHILD,
			 90, 250, 100, 50, hwnd,(HMENU)ID_BUTTON1,GetModuleHandle( NULL ),NULL);
			
	        button2 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "button2", WS_VISIBLE|WS_CHILD,
			 190, 250, 100, 50, hwnd,(HMENU)ID_BUTTON2,GetModuleHandle( NULL ),NULL);			
	         
			editTotal = CreateWindowEx (WS_EX_CLIENTEDGE,"EDIT", "edit1",       
	        WS_VISIBLE|WS_CHILD, 20, 110, 400, 50, hwnd, NULL, g_inst, NULL );

			edit2 = CreateWindowEx (WS_EX_CLIENTEDGE,"EDIT", "edit2",       
	        WS_VISIBLE|WS_CHILD, 20, 150, 400, 50, hwnd, NULL, g_inst, NULL );
	
	        staticTextField2 = CreateWindow("STATIC", "static2", WS_VISIBLE | 
	         WS_CHILD | WS_BORDER, 20, 200, 300, 20, hwnd, NULL, NULL, NULL);
	         
	        break;	
		case WM_CTLCOLORSTATIC:

			if(staticTextField1 == hWndControl){
				hdcStatic = GetDC(hWndControl);
				SetTextColor(hdcStatic, RGB(255, 0, 0));
				SetBkMode(hdcStatic, TRANSPARENT);
				}
			
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
	
	//wc.lpszMenuName =  MAKEINTRESOURCE(IDR_MEUMENU); 
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
