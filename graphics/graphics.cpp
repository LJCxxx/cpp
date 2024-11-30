#include "graphics.h"

Graphics::Graphics(HINSTANCE h_instance, int w, int h) : h_instance(h_instance), w(w), h(h) {
  WNDCLASS wc = {};
  wc.lpfnWndProc = window_proc;
  wc.hInstance = h_instance;
  wc.lpszClassName = "GraphicsWindowClass";
  RegisterClass(&wc);

  hwnd = CreateWindowEx(0, "GraphicsWindowClass", "Graphics Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, w, h, NULL, NULL, h_instance, NULL);
  ShowWindow(hwnd, SW_SHOW);
  hdc = GetDC(hwnd);
}

Graphics::~Graphics() {
  ReleaseDC(hwnd, hdc);
  DestroyWindow(hwnd);
}

void Graphics::clear() {
  RECT rect{ 0, 0, w, h };
  FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
}

void Graphics::present() {
}

void Graphics::draw_rectangle(int x, int y, int w, int h, COLORREF color) {
  HBRUSH brush = CreateSolidBrush(color);
  HGDIOBJ old_brush = SelectObject(hdc, brush);
  Rectangle(hdc, x, y, x + w, y + h);
  SelectObject(hdc, old_brush);
  DeleteObject(brush);
}

void Graphics::draw_circle(int x, int y, int rad, COLORREF color) {
  HBRUSH brush = CreateSolidBrush(color);
  HGDIOBJ old_brush = SelectObject(hdc, brush);
  Ellipse(hdc, x - rad, y - rad, x + rad, y + rad);
  SelectObject(hdc, old_brush);
  DeleteObject(brush);
}

LRESULT CALLBACK Graphics::window_proc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param) {
  if (u_msg = WM_DESTROY) {
    PostQuitMessage(0);
    return 0;
  } return DefWindowProc(hwnd, u_msg, w_param, l_param);
}

HWND Graphics::get_window_handle() const {
  return hwnd;
}