#include <windows.h>
#include <engine.h>
#include <iostream>
#include <string>
#include <cmath>

#pragma comment( lib, "libmx.lib"  )
#pragma comment( lib, "libmex.lib" )
#pragma comment( lib, "libeng.lib" )
#pragma comment (lib, "libmat.lib")

const char g_szClassName[] = "myWindowClass";



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    //声明Matlab引擎，并打开
	Engine *m_pEngine;
	m_pEngine=engOpen(NULL);
	engSetVisible(m_pEngine,0);
	
	switch(msg)
    {
        case WM_LBUTTONDOWN:
        {
			//char szFileName[MAX_PATH];
   //         HINSTANCE hInstance = GetModuleHandle(NULL);

   //         GetModuleFileName(hInstance, szFileName, MAX_PATH);
   //         MessageBox(hwnd, szFileName, "This program is:", MB_OK | MB_ICONINFORMATION);
			
			if(m_pEngine==NULL)
			{
				exit(1);
			}
			const int arraysize=1000;
			const double deg=.0174;
			double SinArray[arraysize];

			for(int i=0;i<arraysize;i++)
			{
				SinArray[i]=sin(i*deg);
			}
			//cout<<"example";
			mxArray* SIN =mxCreateDoubleMatrix(arraysize,1,mxREAL);
			memcpy((void*)mxGetPr(SIN),(void*)SinArray,sizeof(double)*arraysize);
			engPutVariable(m_pEngine,"sinegraph",SIN);
			engEvalString(m_pEngine,"figure('units','normalized','outerposition',[0 0 1 1])");
			engEvalString(m_pEngine,"plot(sinegraph),");

			//system("pause");
			//engClose(m_pEngine);

        }
        break;
		case WM_RBUTTONDOWN:
			{
				engEvalString(m_pEngine,"close all");
			}
			break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "The title of my window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}