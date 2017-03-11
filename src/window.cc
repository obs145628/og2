#include "window.hh"
#include <cstdlib>
#include <iostream>
#include "app.hh"
#include "time.hh"

namespace og2
{

  Window::Window(const std::string& title, int width, int height,
                 int x, int y)
    : window_(build_window_(title.c_str(), x, y, width, height, 0))
    , closed_(false)
    , delta_(0)
    , last_render_(Time::now())
    , canvas_(window_)
  {}

  Window::Window(const std::string& title, IVector size,
                 IVector pos)
    : Window(title, size.x, size.y, pos.x, pos.y)
  {}

  Window::~Window()
  {
    SDL_DestroyWindow(window_);
  }


  std::string Window::title_get()
  {
    return SDL_GetWindowTitle(window_);
  }
  
  IVector Window::position_get()
  {
    IVector res;
    SDL_GetWindowPosition(window_, &(res.x), &(res.y));
    return res;
  }
  
  IVector Window::size_get()
  {
    IVector res;
    SDL_GetWindowSize(window_, &(res.x), &(res.y));
    return res;
  }

  void Window::title_set(const std::string& title)
  {
    SDL_SetWindowTitle(window_, title.c_str());
  }
  
  void Window::position_set(const IVector& position)
  {
    SDL_SetWindowPosition(window_, position.x, position.y);
  }
  
  void Window::size_set(const IVector& size)
  {
    SDL_SetWindowSize(window_, size.x, size.y);
  }

  void Window::show()
  {
    SDL_ShowWindow(window_);
  }
  
  void Window::hide()
  {
    SDL_HideWindow(window_);
  }

  long Window::delta_get() const
  {
    return delta_;
  }

  int Window::run()
  {

    while (!closed_)
			{
        poll_events();

        long time = Time::now();
        delta_ = time - last_render_;
        last_render_ = time;


        canvas_.clear();
        render_();
        canvas_.render();
      }

    return 0;
  }

  void Window::close()
  {
    closed_ = true;
  }

  void Window::poll_events()
  {
    SDL_Event e;
    
    while (SDL_PollEvent(&e))
      {
        if (!on_event_(e))
          continue;

        
        if (e.type == SDL_QUIT)
          on_quit_();
        else if (e.type == SDL_MOUSEMOTION)
          on_mouse_move_(MouseMoveEvent{e.motion});
        else if (e.type == SDL_MOUSEBUTTONDOWN)
          on_mouse_down_(MouseClickEvent{e.button});
        else if (e.type == SDL_MOUSEBUTTONUP)
          on_mouse_up_(MouseClickEvent{e.button});
        else if (e.type == SDL_KEYDOWN)
          on_key_down_(KeyboardEvent{e.key});
        else if (e.type == SDL_KEYUP)
          on_key_up_(KeyboardEvent{e.key});
      }
  }


  bool Window::on_event_(const SDL_Event&)
  {
    return true;
  }

  void Window::on_quit_()
  {
    closed_ = true;
  }

  void Window::on_mouse_move_(const MouseMoveEvent&)
  {}
  
  void Window::on_mouse_up_(const MouseClickEvent&)
  {}
  
  void Window::on_mouse_down_(const MouseClickEvent&)
  {}

  void Window::on_key_down_(const KeyboardEvent&)
  {}
  
  void Window::on_key_up_(const KeyboardEvent&)
  {}


  void Window::render_()
  {}

  SDL_Window* Window::build_window_(const char* title, int x, int y,
                                    int w, int h, Uint32 flags)
  {
    og2::App::init();
    auto res = SDL_CreateWindow(title, x, y, w, h, flags);
    if(!res)
      {
        std::cerr << "Error: CreateWindow: "
                  << SDL_GetError() << std::endl;
        exit(1);
      }

    return res;
  }
  
  
}
