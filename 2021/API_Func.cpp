#include "API_Func.h"


HINSTANCE* GHInstance;


ATOM MyRegisterClass(HINSTANCE hInstance,WCHAR *Winclass)
{
    WNDCLASSEXW wcex;


    GHInstance = &hInstance;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2021));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY2021);
    wcex.lpszClassName = Winclass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE* GlobalHInstance,HINSTANCE hInstance,WCHAR* Winclass, WCHAR* WinTitle,int nCmdShow)
{
    *GlobalHInstance = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    HWND hWnd = CreateWindowW(Winclass, WinTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
bool init = FALSE;

Point p1(0, 0);
Point p2(100, 100);
HDC hDc, memDc;
PAINTSTRUCT ps;
HBITMAP MyBitmap, OldBitmap;

Entity Circle(IDB_BITMAP1, 1, &p1);
Entity Square(IDB_BITMAP2, 2, &p2);

std::vector<Entity*> EntityVec;

LRESULT CALLBACK WndProc(HWND hWnd,UINT message, WPARAM wParam, LPARAM lParam)
{
// 이 함수 내에서의 지역 변수 선언 금지
    if (!init) {
        EntityVec.push_back(&Circle);
        EntityVec.push_back(&Square);
    }

    switch (message){

    case WM_KEYDOWN:
    {
        if (wParam == VK_RIGHT) {
            Circle.Position->x += 1;
        }
        else if (wParam == VK_DOWN) {
            Circle.Position->y += 1;
        }
        else if (wParam == VK_LEFT) {
            Circle.Position->x -= 1;
        }
        else if (wParam == VK_UP) {
            Circle.Position->y -= 1;
        }
        InvalidateRgn(hWnd, NULL, TRUE);
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(*GHInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        
        hDc = BeginPaint(hWnd, &ps);
        memDc = CreateCompatibleDC(hDc);





        MyBitmap = LoadBitmap(*GHInstance, MAKEINTRESOURCE(IDB_BITMAP1));
        OldBitmap = (HBITMAP)SelectObject(memDc, MyBitmap);
        BitBlt(hDc, p1.x, p1.y, 400, 400, memDc, 0, 0, SRCCOPY);



        MyBitmap = LoadBitmap(*GHInstance, MAKEINTRESOURCE(IDB_BITMAP2));
        OldBitmap = (HBITMAP)SelectObject(memDc, MyBitmap);
        BitBlt(hDc, p2.x, p2.y, 400, 400, memDc, 0, 0, SRCCOPY);







        SelectObject(memDc, OldBitmap);
        DeleteObject(MyBitmap);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}




// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
