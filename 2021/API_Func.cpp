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
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   �뵵: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   �ּ�:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE* GlobalHInstance,HINSTANCE hInstance,WCHAR* Winclass, WCHAR* WinTitle,int nCmdShow)
{
    *GlobalHInstance = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

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
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
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
// �� �Լ� �������� ���� ���� ���� ����
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
        // �޴� ������ ���� �м��մϴ�:
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




// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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
