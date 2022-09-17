#pragma once

#include "2021.h"
#define MAX_LOADSTRING 100



// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance,WCHAR *Winclass);
BOOL                InitInstance(HINSTANCE* ,HINSTANCE, WCHAR* , WCHAR*, int);
LRESULT CALLBACK    WndProc(HWND,UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);