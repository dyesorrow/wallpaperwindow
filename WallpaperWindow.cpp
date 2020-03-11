#include <tchar.h>
#include <Windows.h>
#include <iostream>

using namespace std;

HWND workerW = nullptr;
BOOL EnumWindowsProc(HWND tophandle, LPARAM topparamhandle)
{
    if (FindWindowEx(tophandle, 0, _T("SHELLDLL_DefView"), nullptr) != nullptr)
        workerW = FindWindowEx(0, tophandle, _T("WorkerW"), 0);
    return true;
}
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Need to enter window name parameter! Example: WallpaperWindow.exe TestWindow" << endl;
        return 0;
    }
    else
    {
        cout << "Set window: " << argv[1] << endl;
    }

    int result;
    HWND h = FindWindow(_T("Progman"), nullptr);
    SendMessageTimeout(h, 0x052c, 0, 0, SMTO_NORMAL, 1000, (PDWORD_PTR)&result);
    EnumWindows(EnumWindowsProc, (LPARAM) nullptr);
    HWND wallpapaer = FindWindowA(nullptr, (LPCSTR)argv[1]);
    HWND rw = SetParent(wallpapaer, h);

    if (rw == nullptr)
    {
        cout << "Error: " << GetLastError() << endl;
    }
    return 0;
}