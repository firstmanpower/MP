#include <windows.h>
#include <strsafe.h>
#include <stdio.h>
#include <tchar.h>
#pragma warning(disable:4996) //fopen 때문에...

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //MAIN
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM); //MZ
LRESULT CALLBACK WndProc3(HWND, UINT, WPARAM, LPARAM); //PE
LRESULT CALLBACK WndProc3_1(HWND, UINT, WPARAM, LPARAM); //PE_1
LRESULT CALLBACK WndProc3_2(HWND, UINT, WPARAM, LPARAM); //PE_2
LRESULT CALLBACK WndProc3_3(HWND, UINT, WPARAM, LPARAM);

HINSTANCE glb_inst;
int glb_nCS;


void DeleteBlank(wchar_t* str) {

    int size = 1;
    int i2 = 0;
    wchar_t* str2;


    for (int i = 0; str[i] != 0; i++) {
        size = i;
    }

    str2 = new wchar_t[size + 2];
    
    for (int i = 0; i < size + 2; i++) {
        str2[i] = 0;
    }

    for (int i = 0; i < size + 2; i++) {
        
        if (str[i] != 32 && str[i] != 9) {
            str2[i2] = str[i];
            i2++;
        }

    }

    for (int i = 0; i < size + 2; i++) {
        str[i] = 0;
    }

    for (int i = 0; i < i2; i++) {
        str[i] = str2[i];
    }

}



void AddString(wchar_t* result, int resultsize, const wchar_t* str1, const wchar_t* str2) {

    int str1size = 0;
    int str2size = 0;

    for (int i = 0; str1[i] != 0; i++) {
        str1size = i;
    }
    for (int i = 0; str2[i] != 0; i++) {
        str2size = i;
    }


    str2size += str1size + 1;

    int i2 = 0;
    int i3 = 0;

    if (resultsize < str2size + 2)return;

    for (int i = 0; i < resultsize; i++) {

        if (i <= str1size) {
            result[i] = str1[i2];
            i2++;
        }

        else if (i <= str2size) {
            result[i] = str2[i3];
            i3++;
        }

        else {
            result[i] = 0;
        }

    }


}

void Run(const wchar_t* name, wchar_t* target1, int target1size) {

    STARTUPINFOW si = { 0 };
    PROCESS_INFORMATION pi = { 0 };

    wchar_t* cal;

    wchar_t* result;

    cal = new wchar_t[target1size + 1];
    result = new wchar_t[target1size + 2 + 30];

    AddString(cal, target1size + 1, L" ", target1);
    AddString(result, target1size + 2 + 30, name, cal);

    si.cb = sizeof(si);

    CreateProcess(0, result, 0, 0, 0, CREATE_NEW_CONSOLE, 0, 0, &si, &pi);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

}

void Run(const wchar_t* name, wchar_t* target1, wchar_t* target2, int target1size, int target2size) {

    STARTUPINFOW si = { 0 };
    PROCESS_INFORMATION pi = { 0 };

    wchar_t* cal;
    wchar_t* cal1;
    wchar_t* cal2;

    wchar_t* result;

    cal = new wchar_t[target1size+1];
    cal1 = new wchar_t[target2size+1];
    cal2 = new wchar_t[target1size + target2size + 2];
    result = new wchar_t[target1size + target2size + 2 + 30];

    AddString(cal, target1size+1, L" ", target1);
    AddString(cal1, target2size+1, L" ", target2);
    AddString(cal2, target1size+target2size+2, cal, cal1);
    AddString(result, target1size+target2size+2+30, name, cal2);

    si.cb = sizeof(si);

    CreateProcess(0, result, 0, 0, 0, CREATE_NEW_CONSOLE, 0, 0, &si, &pi);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PWSTR pCmdLine, int nCmdShow) {

    MSG  msg;
    WNDCLASSW wc = { 0 };
    WNDCLASSW wc2 = { 0 };
    WNDCLASSW wc3 = { 0 };
    WNDCLASSW wc3_1 = { 0 };
    WNDCLASSW wc3_2 = { 0 };
    WNDCLASSW wc3_3 = { 0 };
    HWND hwnd;

    wc.lpszClassName = L"MAIN";
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);

    wc2.lpszClassName = L"MZ";
    wc2.hInstance = hInstance;
    wc2.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc2.lpfnWndProc = WndProc2;
    wc2.hCursor = LoadCursor(0, IDC_ARROW);

    wc3.lpszClassName = L"PE";
    wc3.hInstance = hInstance;
    wc3.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc3.lpfnWndProc = WndProc3;
    wc3.hCursor = LoadCursor(0, IDC_ARROW);

    wc3_1.lpszClassName = L"PE_1";
    wc3_1.hInstance = hInstance;
    wc3_1.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc3_1.lpfnWndProc = WndProc3_1;

    wc3_2.lpszClassName = L"PE_2";
    wc3_2.hInstance = hInstance;
    wc3_2.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc3_2.lpfnWndProc = WndProc3_2;

    wc3_3.lpszClassName = L"CREATE";
    wc3_3.hInstance = hInstance;
    wc3_3.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc3_3.lpfnWndProc = WndProc3_3;

    glb_nCS = nCmdShow;
    glb_inst = hInstance;

    RegisterClassW(&wc);
    RegisterClassW(&wc2);
    RegisterClassW(&wc3);
    RegisterClassW(&wc3_1);
    RegisterClassW(&wc3_2);
    RegisterClassW(&wc3_3);

    hwnd = CreateWindowW(wc.lpszClassName, L"MZ-PE 만드는거 도와주는 프로그램!",
        WS_SYSMENU | WS_VISIBLE,
        300, 100, 350, 250, 0, 0, hInstance, 0);
    
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;

}




LRESULT CALLBACK WndProc3_3(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam) {

    static HWND hwndEdit1;
    static HWND hwndEdit2;
    static HWND hwndEdit3;
    static HWND hwndEdit4;
    static HWND hwndName;
    switch (msg) {

    case WM_CREATE:

        hwndName = CreateWindowW(L"edit", L"Name.txt",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 100, 20, 120, 20,
            hwnd, (HMENU)0, 0, 0);

        CreateWindowW(L"edit", L"MZ",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY, 30, 50, 120, 20,
            hwnd, (HMENU)1, 0, 0);

        hwndEdit1 = CreateWindowW(L"edit", 0,
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 150, 50, 300, 20,
            hwnd, (HMENU)2, 0, 0);

        CreateWindowW(L"edit", L"NT_HEADERS",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY, 30, 80, 120, 20,
            hwnd, (HMENU)3, 0, 0);

        hwndEdit2 = CreateWindowW(L"edit", 0,
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 150, 80, 300, 20,
            hwnd, (HMENU)4, 0, 0);

        CreateWindowW(L"edit", L"FILE_HEADER",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY, 30, 110, 120, 20,
            hwnd, (HMENU)5, 0, 0);

        hwndEdit3 = CreateWindowW(L"edit", 0,
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 150, 110, 300, 20,
            hwnd, (HMENU)6, 0, 0);

        CreateWindowW(L"edit", L"OP_HEADER32",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY, 30, 140, 120, 20,
            hwnd, (HMENU)5, 0, 0);

        hwndEdit4 = CreateWindowW(L"edit", 0,
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 150, 140, 300, 20,
            hwnd, (HMENU)6, 0, 0);

        CreateWindowW(L"button", L"만들기",
            WS_VISIBLE | WS_CHILD, 30, 200, 120, 40,
            hwnd, (HMENU)7, 0, 0);

        break;

    case WM_COMMAND:

        switch (LOWORD(wParam)) {

        case 7:

            int len = GetWindowTextLengthW(hwndEdit1) + 1;
            int len1 = GetWindowTextLengthW(hwndEdit2) + 1;
            int len2 = GetWindowTextLengthW(hwndEdit3) + 1;
            int len3 = GetWindowTextLengthW(hwndEdit4) + 1;
            int len4 = GetWindowTextLengthW(hwndName) + 1;

            wchar_t* buf;
            wchar_t* buf1;
            wchar_t* buf2;
            wchar_t* buf3;
            wchar_t* buf4;

            buf = new wchar_t[len];
            buf1 = new wchar_t[len1];
            buf2 = new wchar_t[len2];
            buf3 = new wchar_t[len3];
            buf4 = new wchar_t[len4];

            GetWindowTextW(hwndEdit1, buf, len);
            GetWindowTextW(hwndEdit2, buf1, len1);
            GetWindowTextW(hwndEdit3, buf2, len2);
            GetWindowTextW(hwndEdit4, buf3, len3);
            GetWindowTextW(hwndName, buf4, len4);

            Run(L"Add.exe", buf4, buf, len4, len);
            Sleep(100);
            Run(L"Add.exe", buf4, buf1, len4, len1);
            Sleep(100);
            Run(L"Add.exe", buf4, buf2, len4, len2);
            Sleep(100);
            Run(L"Add.exe", buf4, buf3, len4, len3);
            Sleep(100);
            Run(L"StringToHex.exe", buf4, len4);

         break;

        }

        break;

    case WM_DESTROY:
        PostMessage(hwnd, WM_CLOSE, 0, 0);
        break;

    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);

}

LRESULT CALLBACK WndProc3_2(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam) {


    static HWND hwndEdit[62];
    static HWND hwndButton;
    static HWND hwndEdit2;

    switch (msg) {

    case WM_CREATE:

        CreateWindowW(L"static", L"Magic",
            WS_VISIBLE | WS_CHILD, 5, 5, 80, 20,
            hwnd, 0, 0, 0);
        hwndEdit[0] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 25, 80, 20,
            hwnd, (HMENU)1, 0, 0);

        CreateWindowW(L"static", L"MajorLinkerVersion",
            WS_VISIBLE | WS_CHILD, 90, 5, 130, 20,
            hwnd, 0, 0, 0);
        hwndEdit[1] = CreateWindowW(L"edit", L"00",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 90, 25, 130, 20,
            hwnd, (HMENU)2, 0, 0);

        CreateWindowW(L"static", L"MinorLinkerVersion",
            WS_VISIBLE | WS_CHILD, 225, 5, 130, 20,
            hwnd, 0, 0, 0);
        hwndEdit[2] = CreateWindowW(L"edit", L"00",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 225, 25, 130, 20,
            hwnd, (HMENU)3, 0, 0);

        CreateWindowW(L"static", L"SizeOfCode",
            WS_VISIBLE | WS_CHILD, 360, 5, 130, 20,
            hwnd, 0, 0, 0);
        hwndEdit[3] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 360, 25, 80, 20,
            hwnd, (HMENU)4, 0, 0);

        CreateWindowW(L"static", L"SizeOfInitializedData",
            WS_VISIBLE | WS_CHILD, 445, 5, 140, 20,
            hwnd, 0, 0, 0);
        hwndEdit[4] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 445, 25, 140, 20,
            hwnd, (HMENU)5, 0, 0);

        CreateWindowW(L"static", L"SizeOfUninitializedData",
            WS_VISIBLE | WS_CHILD, 5, 45, 155, 20,
            hwnd, 0, 0, 0);
        hwndEdit[5] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 65, 155, 20,
            hwnd, (HMENU)6, 0, 0);

        CreateWindowW(L"static", L"SizeOfUninitializedData",
            WS_VISIBLE | WS_CHILD, 5, 45, 155, 20,
            hwnd, 0, 0, 0);

        hwndEdit[6] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 165, 65, 140, 20,
            hwnd, (HMENU)7, 0, 0);

        CreateWindowW(L"static", L"AddressOfEntryPoint",
            WS_VISIBLE | WS_CHILD, 165, 45, 140, 20,
            hwnd, 0, 0, 0);

        hwndEdit[7] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 310, 65, 80, 20,
            hwnd, (HMENU)8, 0, 0);

        CreateWindowW(L"static", L"BaseOfCode",
            WS_VISIBLE | WS_CHILD, 310, 45, 80, 20,
            hwnd, 0, 0, 0);
        
        hwndEdit[8] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 395, 65, 80, 20,
            hwnd, (HMENU)9, 0, 0);

        CreateWindowW(L"static", L"BaseOfData",
            WS_VISIBLE | WS_CHILD, 395, 45, 80, 20,
            hwnd, 0, 0, 0);

        hwndEdit[9] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 480, 65, 80, 20,
            hwnd, (HMENU)10, 0, 0);

        CreateWindowW(L"static", L"ImageBase",
            WS_VISIBLE | WS_CHILD, 480, 45, 80, 20,
            hwnd, 0, 0, 0);

        hwndEdit[10] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 565, 65, 110, 20,
            hwnd, (HMENU)11, 0, 0);

        CreateWindowW(L"static", L"SectionAlignment",
            WS_VISIBLE | WS_CHILD, 565, 45, 120, 20,
            hwnd, 0, 0, 0);

        hwndEdit[11] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 105, 110, 20,
            hwnd, (HMENU)12, 0, 0);

        CreateWindowW(L"static", L"FileAlignment",
            WS_VISIBLE | WS_CHILD, 5, 85, 110, 20,
            hwnd, 0, 0, 0);

        hwndEdit[12] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 120, 105, 200, 20,
            hwnd, (HMENU)13, 0, 0);

        CreateWindowW(L"static", L"MajorOperatingSystemVersion",
            WS_VISIBLE | WS_CHILD, 120, 85, 200, 20,
            hwnd, 0, 0, 0);

        hwndEdit[13] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 325, 105, 200, 20,
            hwnd, (HMENU)14, 0, 0);

        CreateWindowW(L"static", L"MinorOperatingSystemVersion",
            WS_VISIBLE | WS_CHILD, 325, 85, 200, 20,
            hwnd, 0, 0, 0);
        
        hwndEdit[14] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 530, 105, 130, 20,
            hwnd, (HMENU)15, 0, 0);

        CreateWindowW(L"static", L"MajorImageVersion",
            WS_VISIBLE | WS_CHILD, 530, 85, 130, 20,
            hwnd, 0, 0, 0);

        hwndEdit[15] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 145, 130, 20,
            hwnd, (HMENU)16, 0, 0);

        CreateWindowW(L"static", L"MinorImageVersion",
            WS_VISIBLE | WS_CHILD, 5, 125, 130, 20,
            hwnd, 0, 0, 0);

        hwndEdit[16] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 140, 145, 160, 20,
            hwnd, (HMENU)17, 0, 0);

        CreateWindowW(L"static", L"MajorSubsystemVersion",
            WS_VISIBLE | WS_CHILD, 140, 125, 160, 20,
            hwnd, 0, 0, 0);

        hwndEdit[17] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 305, 145, 160, 20,
            hwnd, (HMENU)18, 0, 0);

        CreateWindowW(L"static", L"MinorSubsystemVersion",
            WS_VISIBLE | WS_CHILD, 305, 125, 160, 20,
            hwnd, 0, 0, 0);

        hwndEdit[18] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 470, 145, 130, 20,
            hwnd, (HMENU)19, 0, 0);

        CreateWindowW(L"static", L"Win32VersionValue",
            WS_VISIBLE | WS_CHILD, 470, 125, 130, 20,
            hwnd, 0, 0, 0);

        hwndEdit[19] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 185, 85, 20,
            hwnd, (HMENU)20, 0, 0);

        CreateWindowW(L"static", L"SizeOfImage",
            WS_VISIBLE | WS_CHILD, 5, 165, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[20] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 95, 185, 100, 20,
            hwnd, (HMENU)21, 0, 0);

        CreateWindowW(L"static", L"SizeOfHeaders",
            WS_VISIBLE | WS_CHILD, 95, 165, 100, 20,
            hwnd, 0, 0, 0);

        hwndEdit[21] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 200, 185, 80, 20,
            hwnd, (HMENU)22, 0, 0);

        CreateWindowW(L"static", L"CheckSum",
            WS_VISIBLE | WS_CHILD, 200, 165, 80, 20,
            hwnd, 0, 0, 0);

        hwndEdit[22] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 285, 185, 80, 20,
            hwnd, (HMENU)23, 0, 0);

        CreateWindowW(L"static", L"Subsystem",
            WS_VISIBLE | WS_CHILD, 285, 165, 80, 20,
            hwnd, 0, 0, 0);

        hwndEdit[23] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 370, 185, 120, 20,
            hwnd, (HMENU)24, 0, 0);

        CreateWindowW(L"static", L"DllCharacteristics",
            WS_VISIBLE | WS_CHILD, 370, 165, 120, 20,
            hwnd, 0, 0, 0);

        hwndEdit[24] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 495, 185, 135, 20,
            hwnd, (HMENU)25, 0, 0);

        CreateWindowW(L"static", L"SizeOfStackReserve",
            WS_VISIBLE | WS_CHILD, 495, 165, 135, 20,
            hwnd, 0, 0, 0);
        
        hwndEdit[25] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 225, 130, 20,
            hwnd, (HMENU)26, 0, 0);

        CreateWindowW(L"static", L"SizeOfStackCommit",
            WS_VISIBLE | WS_CHILD, 5, 205, 130, 20,
            hwnd, 0, 0, 0);

        hwndEdit[26] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 140, 225, 135, 20,
            hwnd, (HMENU)27, 0, 0);

        CreateWindowW(L"static", L"SizeOfHeapReserve",
            WS_VISIBLE | WS_CHILD, 140, 205, 135, 20,
            hwnd, 0, 0, 0);

        hwndEdit[27] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 280, 225, 130, 20,
            hwnd, (HMENU)28, 0, 0);

        CreateWindowW(L"static", L"SizeOfHeapCommit",
            WS_VISIBLE | WS_CHILD, 280, 205, 130, 20,
            hwnd, 0, 0, 0);

        hwndEdit[28] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 415, 225, 85, 20,
            hwnd, (HMENU)29, 0, 0);

        CreateWindowW(L"static", L"LoaderFlags",
            WS_VISIBLE | WS_CHILD, 415, 205, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[29] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 505, 225, 145, 20,
            hwnd, (HMENU)30, 0, 0);

        CreateWindowW(L"static", L"NumberOfRvaAndSizes",
            WS_VISIBLE | WS_CHILD, 505, 205, 145, 20,
            hwnd, 0, 0, 0);

        hwndEdit[30] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 265, 210, 20,
            hwnd, (HMENU)32, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[0]:VirtualAddress",
            WS_VISIBLE | WS_CHILD, 5, 245, 210, 20,
            hwnd, 0, 0, 0);

        hwndEdit[31] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 220, 265, 140, 20,
            hwnd, (HMENU)33, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[0]:Size",
            WS_VISIBLE | WS_CHILD, 220, 245, 140, 20,
            hwnd, 0, 0, 0);

        hwndEdit[32] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 365, 265, 210, 20,
            hwnd, (HMENU)34, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[1]:VirtualAddress",
            WS_VISIBLE | WS_CHILD, 365, 245, 210, 20,
            hwnd, 0, 0, 0);

        hwndEdit[33] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 305, 140, 20,
            hwnd, (HMENU)35, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[1]:Size",
            WS_VISIBLE | WS_CHILD, 5, 285, 140, 20,
            hwnd, 0, 0, 0);

        hwndEdit[34] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 150, 305, 210, 20,
            hwnd, (HMENU)36, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[2]:VirtualAddress",
            WS_VISIBLE | WS_CHILD, 150, 285, 210, 20,
            hwnd, 0, 0, 0);

        hwndEdit[35] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 365, 305, 140, 20,
            hwnd, (HMENU)37, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[2]:Size",
            WS_VISIBLE | WS_CHILD, 365, 285, 140, 20,
            hwnd, 0, 0, 0);

        hwndEdit[36] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 345, 210, 20,
            hwnd, (HMENU)38, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[3]:VirtualAddress",
            WS_VISIBLE | WS_CHILD, 5, 325, 210, 20,
            hwnd, 0, 0, 0);

        hwndEdit[37] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 220, 345, 140, 20,
            hwnd, (HMENU)39, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[3]:Size",
            WS_VISIBLE | WS_CHILD, 220, 325, 140, 20,
            hwnd, 0, 0, 0);

        hwndEdit[38] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 365, 345, 210, 20,
            hwnd, (HMENU)40, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[4]:VirtualAddress",
            WS_VISIBLE | WS_CHILD, 365, 325, 210, 20,
            hwnd, 0, 0, 0);

        hwndEdit[39] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 385, 140, 20,
            hwnd, (HMENU)41, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[4]:Size",
            WS_VISIBLE | WS_CHILD, 5, 365, 140, 20,
            hwnd, 0, 0, 0);

        hwndEdit[40] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 150, 385, 210, 20,
            hwnd, (HMENU)42, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[5]:VirtualAddress",
            WS_VISIBLE | WS_CHILD, 150, 365, 210, 20,
            hwnd, 0, 0, 0);

        hwndEdit[41] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 365, 385, 140, 20,
            hwnd, (HMENU)43, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[5]:Size",
            WS_VISIBLE | WS_CHILD, 365, 365, 140, 20,
            hwnd, 0, 0, 0);

        hwndEdit[42] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 425, 210, 20,
            hwnd, (HMENU)44, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[6]:VirtualAddress",
            WS_VISIBLE | WS_CHILD, 5, 405, 210, 20,
            hwnd, 0, 0, 0);

        hwndEdit[43] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 220, 425, 140, 20,
            hwnd, (HMENU)45, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[6]:Size",
            WS_VISIBLE | WS_CHILD, 220, 405, 140, 20,
            hwnd, 0, 0, 0);

        hwndEdit[44] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 365, 425, 210, 20,
            hwnd, (HMENU)46, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[7]:VirtualAddress",
            WS_VISIBLE | WS_CHILD, 365, 405, 210, 20,
            hwnd, 0, 0, 0);

        hwndEdit[45] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 465, 140, 20,
            hwnd, (HMENU)47, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[7]:Size",
            WS_VISIBLE | WS_CHILD, 5, 445, 140, 20,
            hwnd, 0, 0, 0);

        hwndEdit[46] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 150, 465, 210, 20,
            hwnd, (HMENU)48, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[8]:VirtualAddress",
            WS_VISIBLE | WS_CHILD, 150, 445, 210, 20,
            hwnd, 0, 0, 0);

        hwndEdit[47] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 365, 465, 140, 20,
            hwnd, (HMENU)49, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[8]:Size",
            WS_VISIBLE | WS_CHILD, 365, 445, 140, 20,
            hwnd, 0, 0, 0);

        hwndEdit[48] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 505, 210, 20,
            hwnd, (HMENU)50, 0, 0);

        CreateWindowW( L"static", L"DataDirectory[9]:VirtualAddress",
            WS_VISIBLE | WS_CHILD, 5, 485, 210, 20,
            hwnd, 0, 0, 0);

        hwndEdit[49] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 220, 505, 140, 20,
            hwnd, (HMENU)51, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[9]:Size",
            WS_VISIBLE | WS_CHILD, 220, 485, 140, 20,
            hwnd, 0, 0, 0);

        hwndEdit[50] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 365, 505, 215, 20,
            hwnd, (HMENU)52, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[10]:VirtualAddress",
            WS_VISIBLE | WS_CHILD, 365, 485, 215, 20,
            hwnd, 0, 0, 0);

        hwndEdit[51] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 545, 145, 20,
            hwnd, (HMENU)53, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[10]:Size",
            WS_VISIBLE | WS_CHILD, 5, 525, 145, 20,
            hwnd, 0, 0, 0);


        hwndEdit[52] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 155, 545, 215, 20,
            hwnd, (HMENU)54, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[11]:VirtualAddress",
            WS_VISIBLE | WS_CHILD, 155, 525, 215, 20,
            hwnd, 0, 0, 0);

        hwndEdit[53] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 375, 545, 145, 20,
            hwnd, (HMENU)55, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[11]:Size",
            WS_VISIBLE | WS_CHILD, 375, 525, 145, 20,
            hwnd, 0, 0, 0);

        hwndEdit[54] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 585, 215, 20,
            hwnd, (HMENU)56, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[12]:VirtualAddress",
            WS_VISIBLE | WS_CHILD, 5, 565, 215, 20,
            hwnd, 0, 0, 0);

        hwndEdit[55] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 225, 585, 145, 20,
            hwnd, (HMENU)57, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[12]:Size",
            WS_VISIBLE | WS_CHILD, 225, 565, 145, 20,
            hwnd, 0, 0, 0);

        hwndEdit[56] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 375, 585, 215, 20,
            hwnd, (HMENU)58, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[13]:VirtualAddress",
            WS_VISIBLE | WS_CHILD, 375, 565, 215, 20,
            hwnd, 0, 0, 0);

        hwndEdit[57] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 625, 145, 20,
            hwnd, (HMENU)59, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[13]:Size",
            WS_VISIBLE | WS_CHILD, 5, 605, 145, 20,
            hwnd, 0, 0, 0);

        hwndEdit[58] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 155, 625, 215, 20,
            hwnd, (HMENU)60, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[14]:VirtualAddress",
            WS_VISIBLE | WS_CHILD, 155, 605, 215, 20,
            hwnd, 0, 0, 0);

        hwndEdit[59] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 375, 625, 145, 20,
            hwnd, (HMENU)61, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[14]:Size",
            WS_VISIBLE | WS_CHILD, 375, 605, 145, 20,
            hwnd, 0, 0, 0);

        hwndEdit[60] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 665, 215, 20,
            hwnd, (HMENU)62, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[15]:VirtualAddress",
            WS_VISIBLE | WS_CHILD, 5, 645, 215, 20,
            hwnd, 0, 0, 0);

        hwndEdit[61] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 225, 665, 145, 20,
            hwnd, (HMENU)63, 0, 0);

        CreateWindowW(L"static", L"DataDirectory[15]:Size",
            WS_VISIBLE | WS_CHILD, 225, 645, 145, 20,
            hwnd, 0, 0, 0);

        hwndButton = CreateWindowW(L"button", L"적용",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 375, 665, 80, 25,
            hwnd, (HMENU)64, 0, 0);

        hwndEdit2 = CreateWindowW(L"edit", L"IMAGE_OPTIONAL_HEADER.txt",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 460, 665, 80, 25,
            hwnd, (HMENU)65, 0, 0);

        break;

    case WM_COMMAND:

        switch (LOWORD(wParam)) {

        case 64:

            int len2 = GetWindowTextLengthW(hwndEdit2) + 1;
            wchar_t* buf2;
            buf2 = new wchar_t[len2];
            GetWindowTextW(hwndEdit2, buf2, len2);

            FILE* output = _wfopen(buf2, L"w");
            if (output == NULL)break;

            for (int i = 0; i < 62; i++) {

                int len = GetWindowTextLengthW(hwndEdit[i]) + 1;

                wchar_t* buf;
                buf = new wchar_t[len];

                GetWindowTextW(hwndEdit[i], buf, len);

                DeleteBlank(buf);
                _ftprintf(output, L"%s", buf);

            }

            fclose(output);


            break;

        }

        break;

    case WM_DESTROY:
        PostMessage(hwnd, WM_CLOSE, 0, 0);
        break;

    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);


}

LRESULT CALLBACK WndProc3_1(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam) {

    static HWND hwndEdit[7];
    static HWND hwndEdit2;
    static HWND hwndButton;
    switch (msg) {

    case WM_CREATE:

        CreateWindowW(L"static", L"Machine",
            WS_VISIBLE | WS_CHILD, 5, 5, 80, 20,
            hwnd, 0, 0, 0);
        hwndEdit[0] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 25, 80, 20,
            hwnd, (HMENU)1, 0, 0);

        CreateWindowW(L"static", L"NumberOfSections",
            WS_VISIBLE | WS_CHILD, 90, 5, 130, 20,
            hwnd, 0, 0, 0);

        hwndEdit[1] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 90, 25, 125, 20,
            hwnd, (HMENU)2, 0, 0);

        CreateWindowW(L"static", L"TimeDateStamp",
            WS_VISIBLE | WS_CHILD, 220, 5, 110, 20,
            hwnd, 0, 0, 0);

        hwndEdit[2] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 220, 25, 110, 20,
            hwnd, (HMENU)3, 0, 0);

        CreateWindowW(L"static", L"PointerToSymbolTable",
            WS_VISIBLE | WS_CHILD, 335, 5, 150, 20,
            hwnd, 0, 0, 0);

        hwndEdit[3] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 335, 25, 150, 20,
            hwnd, (HMENU)4, 0, 0);

        CreateWindowW(L"static", L"NumberOfSymbol",
            WS_VISIBLE | WS_CHILD, 5, 45, 120, 20,
            hwnd, 0, 0, 0);

        hwndEdit[4] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 65, 120, 20,
            hwnd, (HMENU)5, 0, 0);

        CreateWindowW(L"static", L"SizeOfOptionalHeader",
            WS_VISIBLE | WS_CHILD, 130, 45, 145, 20,
            hwnd, 0, 0, 0);

        hwndEdit[5] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 130, 65, 145, 20,
            hwnd, (HMENU)6, 0, 0);

        CreateWindowW(L"static", L"Characteristics",
            WS_VISIBLE | WS_CHILD, 280, 45, 100, 20,
            hwnd, 0, 0, 0);

        hwndEdit[6] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 280, 65, 100, 20,
            hwnd, (HMENU)7, 0, 0);

        hwndButton = CreateWindowW(L"button", L"적용",
            WS_VISIBLE | WS_CHILD | WS_BORDER, 5, 95, 80, 25,
            hwnd, (HMENU)8, 0, 0);

        hwndEdit2 = CreateWindowW(L"edit", L"IMAGE_FILE_HEADER.txt",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 90, 95, 80, 25,
            hwnd, (HMENU)9, 0, 0);
        break;
        

    case WM_COMMAND:

        switch (LOWORD(wParam)) {

        case 8:

            int len2 = GetWindowTextLengthW(hwndEdit2) + 1;
            wchar_t* buf2;
            buf2 = new wchar_t[len2];
            GetWindowTextW(hwndEdit2, buf2, len2);

            FILE* output = _wfopen(buf2, L"w");
            if (output == NULL)break;

            for (int i = 0; i < 7; i++) {

                int len = GetWindowTextLengthW(hwndEdit[i]) + 1;

                wchar_t* buf;
                buf = new wchar_t[len];

                GetWindowTextW(hwndEdit[i], buf, len);

                DeleteBlank(buf);
                _ftprintf(output, L"%s", buf);

            }

            fclose(output);

        break;

        }

        break;

    case WM_DESTROY:
        PostMessage(hwnd, WM_CLOSE, 0, 0);
        break;

    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);


}


LRESULT CALLBACK WndProc3(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam) {

    static HWND hwndEdit[2];
    static HWND hB_IMAGE_FILE_HEADER;
    static HWND hB_IMAGE_OPTIONAL_HEADER32;

    switch (msg) {

    case WM_CREATE:

        CreateWindowW(L"static", L"Signature",
            WS_VISIBLE | WS_CHILD, 5, 5, 80, 20,
            hwnd, 0, 0, 0);
        hwndEdit[0] = CreateWindowW(L"edit", L"5045 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY, 5, 25, 80, 20,
            hwnd, (HMENU)1, 0, 0);

        hB_IMAGE_FILE_HEADER = CreateWindowW(L"button", L"IMAGE_FILE_HEADER",
            WS_VISIBLE | WS_CHILD, 5, 50, 200, 20,
            hwnd, (HMENU)2, 0, 0);

        hB_IMAGE_OPTIONAL_HEADER32 = CreateWindowW(L"button", L"IMAGE_OPTIONAL_HEADER32",
            WS_VISIBLE | WS_CHILD, 5, 75, 200, 20,
            hwnd, (HMENU)3, 0, 0);

        CreateWindowW(L"button", L"적용",
            WS_VISIBLE | WS_CHILD, 5, 100, 80, 25,
            hwnd, (HMENU)4, 0, 0);

        hwndEdit[1] = CreateWindowW(L"edit", L"PE.txt",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 90, 100, 80, 25,
            hwnd, (HMENU)5, 0, 0);

    break;

    case WM_COMMAND:

        switch (LOWORD(wParam)) {

        case 2:

            CreateWindowW(L"PE_1", L"IMAGE_FILE_HEADER",
                WS_SYSMENU | WS_VISIBLE,
                100, 100, 600, 200, 0, 0, glb_inst, 0);

        break;

        case 3:

            CreateWindowW(L"PE_2", L"IMAGE_OPTIONAL_HEADER32",
                WS_SYSMENU | WS_VISIBLE,
                100, 0, 700, 900, 0, 0, glb_inst, 0);

        break;

        case 4:

            int len2 = GetWindowTextLengthW(hwndEdit[1]) + 1;
            wchar_t* buf2;
            buf2 = new wchar_t[len2];
            GetWindowTextW(hwndEdit[1], buf2, len2);

            FILE* output = _wfopen(buf2, L"w");
            if (output == NULL)break;

            int len = GetWindowTextLengthW(hwndEdit[0]) + 1;

            wchar_t* buf;
            buf = new wchar_t[len];

            GetWindowTextW(hwndEdit[0], buf, len);

            DeleteBlank(buf);
            _ftprintf(output, L"%lls", buf);

            fclose(output);
        
            break;


        }

    break;

    case WM_DESTROY:
        PostMessage(hwnd, WM_CLOSE, 0, 0);
        break;

    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);


}


LRESULT CALLBACK WndProc2(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam) {

    static HWND hwndEdit[31];
    static HWND hwndEdit2;
    static HWND hwndButton;
    static int value;
    switch (msg) {

    case WM_CREATE:
        
        CreateWindowW(L"static", L"e_magic",
            WS_VISIBLE | WS_CHILD, 5, 10, 80, 20,
            hwnd, 0, 0, 0);

        hwndEdit[0] = CreateWindowW(L"edit", L"4D5A",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY, 5, 30, 80, 20,
            hwnd, (HMENU)1, 0, 0);
        
        CreateWindowW(L"static", L"e_cblp",
            WS_VISIBLE | WS_CHILD, 90, 10, 80, 20,
            hwnd, 0, 0, 0);

        hwndEdit[1] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 90, 30, 80, 20,
            hwnd, (HMENU)2, 0, 0);

        CreateWindowW(L"static", L"e_cp",
            WS_VISIBLE | WS_CHILD, 175, 10, 80, 20,
            hwnd, 0, 0, 0);

        hwndEdit[2] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 175, 30, 80, 20,
            hwnd, (HMENU)3, 0, 0);

        CreateWindowW(L"static", L"e_crlc",
            WS_VISIBLE | WS_CHILD, 260, 10, 80, 20,
            hwnd, 0, 0, 0);

        hwndEdit[3] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 260, 30, 80, 20,
            hwnd, (HMENU)4, 0, 0);

        CreateWindowW(L"static", L"e_cparhdr",
            WS_VISIBLE | WS_CHILD, 345, 10, 80, 20,
            hwnd, 0, 0, 0);

        hwndEdit[4] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 345, 30, 80, 20,
            hwnd, (HMENU)5, 0, 0);

        CreateWindowW(L"static", L"e_minalloc",
            WS_VISIBLE | WS_CHILD, 5, 50, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[5] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 70, 80, 20,
            hwnd, (HMENU)6, 0, 0);

        CreateWindowW(L"static", L"e_maxalloc",
            WS_VISIBLE | WS_CHILD, 90, 50, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[6] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 90, 70, 80, 20,
            hwnd, (HMENU)7, 0, 0);

        CreateWindowW(L"static", L"e_ss",
            WS_VISIBLE | WS_CHILD, 175, 50, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[7] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 175, 70, 80, 20,
            hwnd, (HMENU)8, 0, 0);

        CreateWindowW(L"static", L"e_sp",
            WS_VISIBLE | WS_CHILD, 260, 50, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[8] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 260, 70, 80, 20,
            hwnd, (HMENU)9, 0, 0);

        CreateWindowW(L"static", L"e_csum",
            WS_VISIBLE | WS_CHILD, 345, 50, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[9] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 345, 70, 80, 20,
            hwnd, (HMENU)10, 0, 0);

        CreateWindowW(L"static", L"e_ip",
            WS_VISIBLE | WS_CHILD, 5, 90, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[10] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 110, 80, 20,
            hwnd, (HMENU)11, 0, 0);

        CreateWindowW(L"static", L"e_cs",
            WS_VISIBLE | WS_CHILD, 90, 90, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[11] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 90, 110, 80, 20,
            hwnd, (HMENU)12, 0, 0);

        CreateWindowW(L"static", L"e_lfarlc",
            WS_VISIBLE | WS_CHILD, 175, 90, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[12] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 175, 110, 80, 20,
            hwnd, (HMENU)13, 0, 0);
        
        CreateWindowW(L"static", L"e_ovno",
            WS_VISIBLE | WS_CHILD, 260, 90, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[13] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 260, 110, 80, 20,
            hwnd, (HMENU)14, 0, 0);

        CreateWindowW(L"static", L"e_res[0]",
            WS_VISIBLE | WS_CHILD, 345, 90, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[14] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 345, 110, 80, 20,
            hwnd, (HMENU)15, 0, 0);

        CreateWindowW(L"static", L"e_res[1]",
            WS_VISIBLE | WS_CHILD, 5, 130, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[15] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 150, 80, 20,
            hwnd, (HMENU)16, 0, 0);

        CreateWindowW(L"static", L"e_res[2]",
            WS_VISIBLE | WS_CHILD, 90, 130, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[16] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 90, 150, 80, 20,
            hwnd, (HMENU)17, 0, 0);

        CreateWindowW(L"static", L"e_res[3]",
            WS_VISIBLE | WS_CHILD, 175, 130, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[17] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 175, 150, 80, 20,
            hwnd, (HMENU)18, 0, 0);

        CreateWindowW(L"static", L"e_oemid",
            WS_VISIBLE | WS_CHILD, 260, 130, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[18] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 260, 150, 80, 20,
            hwnd, (HMENU)19, 0, 0);

        CreateWindowW(L"static", L"e_oeminfo",
            WS_VISIBLE | WS_CHILD, 345, 130, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[19] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 345, 150, 80, 20,
            hwnd, (HMENU)20, 0, 0);
        
        CreateWindowW(L"static", L"e_res2[0]",
            WS_VISIBLE | WS_CHILD, 5, 170, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[20] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 190, 80, 20,
            hwnd, (HMENU)21, 0, 0);

        CreateWindowW(L"static", L"e_res2[1]",
            WS_VISIBLE | WS_CHILD, 90, 170, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[21] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 90, 190, 80, 20,
            hwnd, (HMENU)22, 0, 0);

        CreateWindowW(L"static", L"e_res2[2]",
            WS_VISIBLE | WS_CHILD, 175, 170, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[22] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 175, 190, 80, 20,
            hwnd, (HMENU)23, 0, 0);

        CreateWindowW(L"static", L"e_res2[3]",
            WS_VISIBLE | WS_CHILD, 260, 170, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[23] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 260, 190, 80, 20,
            hwnd, (HMENU)24, 0, 0);

        CreateWindowW(L"static", L"e_res2[4]",
            WS_VISIBLE | WS_CHILD, 345, 170, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[24] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 345, 190, 80, 20,
            hwnd, (HMENU)25, 0, 0);


        CreateWindowW(L"static", L"e_res2[5]",
            WS_VISIBLE | WS_CHILD, 5, 210, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[25] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 230, 80, 20,
            hwnd, (HMENU)26, 0, 0);

        CreateWindowW(L"static", L"e_res2[6]",
            WS_VISIBLE | WS_CHILD, 90, 210, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[26] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 90, 230, 80, 20,
            hwnd, (HMENU)27, 0, 0);

        CreateWindowW(L"static", L"e_res2[7]",
            WS_VISIBLE | WS_CHILD, 175, 210, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[27] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 175, 230, 80, 20,
            hwnd, (HMENU)28, 0, 0);

        CreateWindowW(L"static", L"e_res2[8]",
            WS_VISIBLE | WS_CHILD, 260, 210, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[28] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 260, 230, 80, 20,
            hwnd, (HMENU)29, 0, 0);

        CreateWindowW(L"static", L"e_res2[9]",
            WS_VISIBLE | WS_CHILD, 345, 210, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[29] = CreateWindowW(L"edit", L"0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 345, 230, 80, 20,
            hwnd, (HMENU)30, 0, 0);

        CreateWindowW(L"static", L"e_lfanew",
            WS_VISIBLE | WS_CHILD, 5, 250, 85, 20,
            hwnd, 0, 0, 0);

        hwndEdit[30] = CreateWindowW(L"edit", L"0000 0000",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_UPPERCASE, 5, 270, 80, 20,
            hwnd, (HMENU)31, 0, 0);

        hwndButton = CreateWindowW(L"button", L"적용",
            WS_VISIBLE | WS_CHILD | WS_BORDER, 90, 270, 80, 25,
            hwnd, (HMENU)32, 0, 0);

        hwndEdit2 = CreateWindowW(L"edit", L"MZ.txt",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 175, 270, 80, 25,
            hwnd, (HMENU)31, 0, 0);

        break;

    case WM_COMMAND:

        switch (LOWORD(wParam)) {

        case 32:

            int len2 = GetWindowTextLengthW(hwndEdit2) + 1;
            wchar_t* buf2;
            buf2 = new wchar_t[len2];
            GetWindowTextW(hwndEdit2, buf2, len2);
            
            FILE* output = _wfopen(buf2, L"w");
            if (output == NULL)break;

            for (int i = 0; i < 31; i++) {

                int len = GetWindowTextLengthW(hwndEdit[i]) + 1;

                wchar_t* buf;
                buf = new wchar_t[len];

                GetWindowTextW(hwndEdit[i], buf, len);
                
                DeleteBlank(buf);

                fwprintf(output, L"%s", buf);
            }

            fclose(output);
            
            break;


        }

        break;

    case WM_DESTROY:
        PostMessage(hwnd, WM_CLOSE, 0, 0);
        break;

    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);

}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam) {


    switch (msg) {

    case WM_CREATE:

        CreateWindowW(L"button", L"MZ",
            WS_VISIBLE | WS_CHILD, 50, 100, 80, 25,
            hwnd, (HMENU)0, 0, 0);

        CreateWindowW(L"button", L"PE",
            WS_VISIBLE | WS_CHILD, 50, 150, 80, 25,
            hwnd, (HMENU)1, 0, 0);

        CreateWindowW(L"button", L"만들기",
            WS_VISIBLE | WS_CHILD, 50, 50, 80, 25,
            hwnd, (HMENU)2, 0, 0);

        break;

    case WM_COMMAND:

        switch (LOWORD(wParam)) {

        case 0:

            CreateWindowW(L"MZ", L"MZ",
                WS_SYSMENU | WS_VISIBLE,
                100, 100, 445, 400, 0, 0, glb_inst, 0);

            break;
        case 1:

            CreateWindowW(L"PE", L"PE",
                WS_SYSMENU | WS_VISIBLE,
                100, 100, 300, 300, 0, 0, glb_inst, 0);

            break;

        case 2:

            CreateWindowW(L"CREATE", L"만들기",
                WS_SYSMENU | WS_VISIBLE,
                100, 100, 500, 350, 0, 0, glb_inst, 0);

            break;
        }

         break;

    case WM_DESTROY:
        PostQuitMessage(0);
    break;

    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}