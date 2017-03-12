#include "my-win.hh"

using og2::IVector;
using og2::IRect;
using og2::Color;

MyWin::MyWin()
  : Window("test", 640, 480)
  , x1_(50)
  , y1_(100)
  , x2_(10)
  , y2_(250)
{
  og2::App::ressources_root_set("..");
  //canvas_.background_set(Color::BLUE);
   verts_ = {IVector{300, 200}, IVector{400, 200}, IVector{370, 290},
             IVector{300, 235}, IVector{330, 215}, IVector{345, 235},
             IVector{345, 210}};
}

void MyWin::render_()
{

  //canvas_.thickness_set(2);
  //canvas_.color_set(Color::RED);
  //canvas_.draw_rect(IVector{300, 200}, IVector{100, 50});
 
  
  //canvas_.color_set(Color::BLACK);
  canvas_.draw_polygon(verts_);

  

  /*
  canvas_.draw_image(PATH_TEXT, IRect{x1_, y1_, 200, 100});

  canvas_.draw_image_clip(PATH_TEXT, IRect{300, 300, 150, 150},
                          IRect{0, 0, 150, 100});

  canvas_.color_set(Color::RED);
  canvas_.draw_polygon({IVector{500, 30},
        IVector{500, 450},
          IVector{400, 240}});

  canvas_.color_set(Color::YELLOW);
  canvas_.draw_rect(IVector{10, 10}, IVector{30, 200});

  canvas_.color_set(Color::GREEN);
  canvas_.fill_rect(IVector{x2_, y2_}, IVector{30, 200});

  canvas_.draw_text(IVector{200, 200}, PATH_FONT, 29,
                    Color::RED, "You can do it");
  */
}

void MyWin::on_mouse_move_(const og2::MouseMoveEvent& e)
{
  x2_ = e.x;
  y2_ = e.y;

  if (poly_coll_(e.x, e.y, verts_))
    canvas_.color_set(Color::RED);
  else
    canvas_.color_set(Color::BLACK);
}

void MyWin::on_mouse_up_(const og2::MouseClickEvent& e)
{
  x1_ = e.x;
  y1_ = e.y;
}

void MyWin::on_key_down_(const og2::KeyboardEvent& e)
{
  if (e.code == SDLK_q && (e.mod & og2::Keyboard::CTRL))
    close();
}


bool MyWin::poly_coll_(int x, int y, const std::vector<og2::IVector>& vs)
{
  bool b = false;
  
	for(std::size_t i = 0, j = vs.size() - 1; i < vs.size(); j = i, ++i)
    {
      if (((y >= vs[i].y) != (y >= vs[j].y))
          &&
          ( (y - vs[i].y) * (vs[j].x - vs[i].x) / (vs[j].y - vs[i].y)
            + vs[i].x) >= x)
        {
          b = !b;
        }
    }
	return b;
}
