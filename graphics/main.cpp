#include <Windows.h>
#include "graphics.h"

int WINAPI WinMain(HINSTANCE h_instance, HINSTANCE, LPSTR, int) {
  Graphics graphics(h_instance, 800, 600);
  
  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  
  graphics.clear();
  graphics.draw_rectangle(100, 100, 200, 150, RGB(255, 0, 0));
  graphics.draw_circle(400, 300, 50, RGB(0, 0, 255));
  graphics.present();
  
  return 0;
}
