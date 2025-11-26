#include <windows.h>
#include <commctrl.h>
#include <dwmapi.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <queue>
#include <stack>
#include <thread>
#include <chrono>
#include "InvestmentData.h"
#include "DataCalculation.h"
#include "resource.h"

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "dwmapi.lib")

#define ID_CALCULATE_BUTTON 1
#define ID_LISTVIEW         2
#define ID_THEME_TOGGLE     3

using namespace std;

HWND hPrincipalInput, hDepositInput, hInterestInput, hYearsInput;
HWND hCalculateButton, hListView, hThemeToggle;
HFONT hModernFont = NULL;
bool gDarkMode = false;

COLORREF darkBg = RGB(32, 32, 32);
COLORREF darkText = RGB(220, 220, 220);
HBRUSH hDarkBrush = CreateSolidBrush(darkBg);

std::wstring ToWString(double val) {
    std::wstringstream ss;
    ss << std::fixed << std::setprecision(2) << val;
    return ss.str();
}

void ApplyModernFont(HWND hwnd) {
    SendMessage(hwnd, WM_SETFONT, (WPARAM)hModernFont, TRUE);
}

void SetupListView(HWND hwnd) {
    LVCOLUMN col = {};
    col.mask = LVCF_TEXT | LVCF_WIDTH;

    col.pszText = const_cast<LPWSTR>(L"Year");
    col.cx = 80;
    ListView_InsertColumn(hwnd, 0, &col);

    col.pszText = const_cast<LPWSTR>(L"Interest Earned");
    col.cx = 150;
    ListView_InsertColumn(hwnd, 1, &col);

    col.pszText = const_cast<LPWSTR>(L"Ending Balance");
    col.cx = 150;
    ListView_InsertColumn(hwnd, 2, &col);
}

void PopulateListView(HWND hwnd) {
    InvestmentData data;
    wchar_t buffer[100];

    GetWindowTextW(hPrincipalInput, buffer, 100);
    data.SetInitialInvestment(_wtof(buffer));
    GetWindowTextW(hDepositInput, buffer, 100);
    data.SetMonthlyDeposit(_wtof(buffer));
    GetWindowTextW(hInterestInput, buffer, 100);
    data.SetAnnualInterest(_wtof(buffer));
    GetWindowTextW(hYearsInput, buffer, 100);
    data.SetYears(_wtoi(buffer));
    data.SetCurrency('$');

    ListView_DeleteAllItems(hwnd);

    std::queue<double> q;
    std::stack<double> s;
    std::vector<YearRecord> results = DataCalculation::CalculateYearlyResults(data, true, q, s);

    for (int i = 0; i < results.size(); ++i) {
        LVITEM item = {};
        item.mask = LVIF_TEXT;
        item.iItem = i;

        std::wstring year = std::to_wstring(results[i].year);
        item.pszText = (LPWSTR)year.c_str();
        ListView_InsertItem(hwnd, &item);

        std::wstring interest = ToWString(results[i].interestEarned);
        ListView_SetItemText(hwnd, i, 1, (LPWSTR)interest.c_str());

        std::wstring balance = ToWString(results[i].endingBalance);
        ListView_SetItemText(hwnd, i, 2, (LPWSTR)balance.c_str());
    }
}

void ResizeControls(HWND hwnd) {
    RECT rc;
    GetClientRect(hwnd, &rc);
    MoveWindow(hListView, 20, 160, rc.right - 40, rc.bottom - 180, TRUE);
}

void ToggleTheme(HWND hwnd) {
    gDarkMode = !gDarkMode;
    BOOL dark = gDarkMode ? TRUE : FALSE;
    DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &dark, sizeof(dark));

    HBRUSH hbr = CreateSolidBrush(gDarkMode ? darkBg : RGB(245, 245, 245));
    SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)hbr);

    // Apply theme to child controls
    HWND hChild = GetWindow(hwnd, GW_CHILD);
    while (hChild) {
        if (gDarkMode) {
            // Apply dark mode text and background for supported controls
            wchar_t className[32];
            GetClassNameW(hChild, className, 32);

            if (wcscmp(className, L"Button") == 0 || wcscmp(className, L"Static") == 0 || wcscmp(className, L"Edit") == 0) {
                SetTextColor(GetDC(hChild), darkText);
                SetBkColor(GetDC(hChild), darkBg);
                SetClassLongPtr(hChild, GCLP_HBRBACKGROUND, (LONG_PTR)hDarkBrush);
            }
            else if (wcscmp(className, WC_LISTVIEW) == 0) {
                ListView_SetTextBkColor(hChild, darkBg);
                ListView_SetBkColor(hChild, darkBg);
                ListView_SetTextColor(hChild, darkText);
            }
        }
        else {
            // Reset to default system colors if needed
        }

        hChild = GetWindow(hChild, GW_HWNDNEXT);
    }

    InvalidateRect(hwnd, NULL, TRUE);
    UpdateWindow(hwnd);
}


void ShowSplashScreen(HINSTANCE hInstance) {
    const wchar_t SPLASH_CLASS[] = L"SplashWindowClass";

    WNDCLASSW splashWc = {};
    splashWc.lpfnWndProc = DefWindowProcW;
    splashWc.hInstance = hInstance;
    splashWc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    splashWc.lpszClassName = SPLASH_CLASS;
    RegisterClassW(&splashWc);

    HWND hSplash = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TOPMOST,
        SPLASH_CLASS, L"", WS_POPUP,
        0, 0, 500, 300,
        NULL, NULL, hInstance, NULL);

    SendMessageW(hSplash, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON)));
    SendMessageW(hSplash, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON)));

    if (!hSplash) return;

    HBITMAP hBmp = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_SPLASH));
    HWND hStatic = CreateWindowW(L"STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP,
        0, 0, 500, 300, hSplash, NULL, hInstance, NULL);
    SendMessageW(hStatic, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmp);

    RECT rc;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);
    int x = rc.left + (rc.right - rc.left - 500) / 2;
    int y = rc.top + (rc.bottom - rc.top - 300) / 2;
    SetWindowPos(hSplash, HWND_TOPMOST, x, y, 500, 300, SWP_SHOWWINDOW);

    ShowWindow(hSplash, SW_SHOWNORMAL);
    UpdateWindow(hSplash);
    SetLayeredWindowAttributes(hSplash, 0, 0, LWA_ALPHA);

    for (int alpha = 0; alpha <= 255; alpha += 15) {
        SetLayeredWindowAttributes(hSplash, 0, (BYTE)alpha, LWA_ALPHA);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        MSG msg;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    for (int alpha = 255; alpha >= 0; alpha -= 15) {
        SetLayeredWindowAttributes(hSplash, 0, (BYTE)alpha, LWA_ALPHA);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        MSG msg;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    DestroyWindow(hSplash);
    DeleteObject(hBmp);
    UnregisterClassW(SPLASH_CLASS, hInstance);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    switch (msg) {

    case WM_CTLCOLORSTATIC:
    case WM_CTLCOLOREDIT:
    case WM_CTLCOLORBTN: {
        HDC hdcStatic = (HDC)wParam;
        if (gDarkMode) {
            SetTextColor(hdcStatic, darkText);
            SetBkColor(hdcStatic, darkBg);
            return (INT_PTR)hDarkBrush;
        }
        break;
    }

    case WM_CREATE: {
        hModernFont = CreateFontW(-12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");

        CreateWindowW(L"STATIC", L"Initial Investment:", WS_VISIBLE | WS_CHILD,
            20, 20, 130, 20, hwnd, NULL, NULL, NULL);
        hPrincipalInput = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,
            160, 20, 100, 20, hwnd, NULL, NULL, NULL);
        SendMessageW(hPrincipalInput, EM_SETCUEBANNER, FALSE, (LPARAM)L"Enter amount");

        CreateWindowW(L"STATIC", L"Monthly Deposit:", WS_VISIBLE | WS_CHILD,
            20, 54, 130, 20, hwnd, NULL, NULL, NULL);
        hDepositInput = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,
            160, 54, 100, 20, hwnd, NULL, NULL, NULL);
        SendMessageW(hDepositInput, EM_SETCUEBANNER, FALSE, (LPARAM)L"Enter deposit");

        CreateWindowW(L"STATIC", L"Annual Interest (%):", WS_VISIBLE | WS_CHILD,
            20, 88, 130, 20, hwnd, NULL, NULL, NULL);
        hInterestInput = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,
            160, 88, 100, 20, hwnd, NULL, NULL, NULL);
        SendMessageW(hInterestInput, EM_SETCUEBANNER, FALSE, (LPARAM)L"Enter rate");

        CreateWindowW(L"STATIC", L"Number of Years:", WS_VISIBLE | WS_CHILD,
            20, 122, 130, 20, hwnd, NULL, NULL, NULL);
        hYearsInput = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,
            160, 122, 100, 20, hwnd, NULL, NULL, NULL);
        SendMessageW(hYearsInput, EM_SETCUEBANNER, FALSE, (LPARAM)L"Enter years");

        hCalculateButton = CreateWindowW(L"BUTTON", L"Calculate", WS_VISIBLE | WS_CHILD | WS_TABSTOP,
            300, 54, 100, 40, hwnd, (HMENU)(INT_PTR)ID_CALCULATE_BUTTON, NULL, NULL);

        hThemeToggle = CreateWindowW(L"BUTTON", L"Toggle Theme", WS_VISIBLE | WS_CHILD | WS_TABSTOP,
            300, 104, 100, 30, hwnd, (HMENU)(INT_PTR)ID_THEME_TOGGLE, NULL, NULL);

        hListView = CreateWindowW(WC_LISTVIEW, L"", WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_SINGLESEL | WS_BORDER,
            20, 160, 440, 280, hwnd, (HMENU)(INT_PTR)ID_LISTVIEW, NULL, NULL);
        ListView_SetExtendedListViewStyle(hListView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
        SetupListView(hListView);

        ApplyModernFont(hPrincipalInput);
        ApplyModernFont(hDepositInput);
        ApplyModernFont(hInterestInput);
        ApplyModernFont(hYearsInput);
        ApplyModernFont(hCalculateButton);
        ApplyModernFont(hThemeToggle);
        ApplyModernFont(hListView);
        break;
    }

    case WM_COMMAND:
        if (LOWORD(wParam) == ID_CALCULATE_BUTTON)
            PopulateListView(hListView);
        else if (LOWORD(wParam) == ID_THEME_TOGGLE)
            ToggleTheme(hwnd);
        break;

    case WM_SIZE:
        ResizeControls(hwnd);
        break;

    case WM_DESTROY:
        DeleteObject(hModernFont);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProcW(hwnd, msg, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    INITCOMMONCONTROLSEX icex = { sizeof(icex), ICC_LISTVIEW_CLASSES };
    InitCommonControlsEx(&icex);

    ShowSplashScreen(hInstance);

    const wchar_t CLASS_NAME[] = L"AirgeadWindow";
    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON));
    wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON));
    wc.hbrBackground = CreateSolidBrush(RGB(245, 245, 245));
    RegisterClassExW(&wc);

    HWND hwnd = CreateWindowExW(0, CLASS_NAME, L"Airgead Investment Calculator",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 520,
        NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
