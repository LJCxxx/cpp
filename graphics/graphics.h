#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <Windows.h>

class Graphics {
public:
  Graphics(HINSTANCE h_instance, int w, int h);
  ~Graphics();

  void clear();
  void present();
  void draw_rectangle(int x, int y, int w, int h, COLORREF color);
  void draw_circle(int x, int y, int rad, COLORREF color);

  HWND get_window_handle() const;

private:
  HINSTANCE h_instance;
  HWND hwnd;
  HDC hdc;
  int w;
  int h;

  static LRESULT CALLBACK window_proc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param);
};

#endif