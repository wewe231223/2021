#pragma once

#include "2021.h"
#define MAX_LOADSTRING 100



// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
ATOM                MyRegisterClass(HINSTANCE hInstance,WCHAR *Winclass);
BOOL                InitInstance(HINSTANCE* ,HINSTANCE, WCHAR* , WCHAR*, int);
LRESULT CALLBACK    WndProc(HWND,UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);