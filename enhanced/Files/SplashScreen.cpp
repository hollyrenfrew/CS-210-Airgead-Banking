#include <windows.h>
#include "resource.h"

LRESULT CALLBACK SplashProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HBITMAP hBitmap;

    switch (msg) {
    case WM_CREATE:
        hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_SPLASH));
        break;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        HDC hdcMem = CreateCompatibleDC(hdc);
        SelectObject(hdcMem, hBitmap);
        BITMAP bmp;
        GetObject(hBitmap, sizeof(BITMAP), &bmp);
        BitBlt(hdc, 0, 0, bmp.bmWidth, bmp.bmHeight, hdcMem, 0, 0, SRCCOPY);
        DeleteDC(hdcMem);
        EndPaint(hwnd, &ps);
        break;
    }

    case WM_DESTROY:
        DeleteObject(hBitmap);
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int ShowSplashScreen(HINSTANCE hInstance) {
    const wchar_t* CLASS_NAME = L"SplashClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = SplashProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TOOLWINDOW, CLASS_NAME, L"",
        WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
        NULL, NULL, hInstance, NULL);

    // Center window
    RECT rc;
    GetWindowRect(hwnd, &rc);
    int width = rc.right - rc.left;
    int height = rc.bottom - rc.top;
    int screenX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
    int screenY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
    SetWindowPos(hwnd, HWND_TOPMOST, screenX, screenY, width, height, SWP_SHOWWINDOW);

    UpdateWindow(hwnd);

    // Splash message loop for 2 seconds
    DWORD startTime = GetTickCount();
    MSG msg;
    while (GetTickCount() - startTime < 2000) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    DestroyWindow(hwnd);
    return 0;
}
