#pragma once

#include <string>
#include "sdl.hh"
#include <utility>
#include "canvas.hh"
#include "events.hh"
#include "vector.hh"

namespace og2
{

  class Window
  {

  public:

    Window(const std::string& title, int width, int height,
           int x = SDL_WINDOWPOS_UNDEFINED,
           int y = SDL_WINDOWPOS_UNDEFINED);
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    ~Window();

    std::string title_get();
    IVector position_get();
    IVector size_get();

    void title_set(const std::string& title);
    void position_set(const IVector& position);
    void size_set(const IVector& size);

    void show();
    void hide();
    long delta_get() const;

    int run();
    void close();
    void poll_events();

  protected:
    
    //on_event called first, then more specifics methods if returns true
    virtual bool on_event_(const SDL_Event& e);
    virtual void on_quit_();
    virtual void on_mouse_move_(const MouseMoveEvent& e);
    virtual void on_mouse_up_(const MouseClickEvent& e);
    virtual void on_mouse_down_(const MouseClickEvent& e);

    virtual void render_();

    static SDL_Window* build_window_(const char* title, int x, int y,
                                     int w, int h, Uint32 flags);

  private:
    SDL_Window* window_;
    bool closed_;
    long delta_;
    long last_render_;


  protected:
    Canvas canvas_;
    
  };
  
}
