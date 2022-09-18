#include "API_Func.h"
#pragma comment(lib, "msimg32.lib")

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
Point p1(0, 0);
Point p2(100, 100);
Point p3(500, 500);

Entity Knight(Knight1, &p3);
Entity Circle(CIRCLE1, &p1);
Entity Square(SQUARE1, &p2);



PAINTSTRUCT ps;
HDC hDc;
RECT rect;


#define FPS 13
#define TIMER_FPS 1
#define TIMER_ANIMATION 2


bool popup = FALSE;
int KnightAni = 1;
std::vector<Entity*> EntityVec;
DCManager DM;

LRESULT CALLBACK WndProc(HWND hWnd,UINT message, WPARAM wParam, LPARAM lParam)
{
// �� �Լ� �������� ���� ���� ���� ����


    switch (message){
    case WM_CREATE:
        EntityVec.push_back(&Knight);
        DM.Resister(&EntityVec);
        SetTimer(hWnd, TIMER_FPS, FPS, NULL);
        SetTimer(hWnd, TIMER_ANIMATION, 200, NULL);
        break;
    case WM_KEYDOWN:
    {
        KnightAni = 2;
        if (wParam == VK_RIGHT) {
            Knight.Position->x += 2;
        }
        else if (wParam == VK_DOWN) {
            Knight.Position->y += 2;
        }
        else if (wParam == VK_LEFT) {
            Knight.Position->x -= 2;
        }
        else if (wParam == VK_UP) {
            Knight.Position->y -= 2;
        }
        break;
    }
    case WM_KEYUP:
        KnightAni = 1;
        break;
    case WM_TIMER:
        if (wParam == TIMER_ANIMATION) {
            KnightAnimation(&Knight, &popup, KnightAni);
            
        }

        InvalidateRect(hWnd, NULL, FALSE);
        UpdateWindow(hWnd);
        break;
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
        GetClientRect(hWnd, &rect);


        BitBlt(hDc, 0, 0, rect.right, rect.bottom,DM.Paint(hWnd, &hDc, GHInstance, &rect), 0, 0, SRCCOPY);

        DM.Free();
        //free�ϴ� ������ ��ü �� �Լ� ����

        EndPaint(hWnd, &ps);

    }
    break;
    case WM_DESTROY:
        KillTimer(hWnd, 1);
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
