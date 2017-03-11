#pragma once

#include "app.hh"
#include "window.hh"

class MyWin : public og2::Window
{
public:

  const char* PATH_TEXT = "misc/texture.png";
  const char* PATH_FONT = "misc/deja-vu-sans-mono.ttf";
  
  MyWin();

protected:
  virtual void render_() override;
  virtual void on_mouse_move_(const og2::MouseMoveEvent& e) override;
  virtual void on_mouse_up_(const og2::MouseClickEvent& e) override;
  virtual void on_key_down_(const og2::KeyboardEvent& e) override;

private:
  int x1_;
  int y1_;
  int x2_;
  int y2_;
  
};
