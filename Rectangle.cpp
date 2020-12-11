#include <iostream>

#include "Rectangle.h"

static void printRectangle(Rectangle const &obj) {
  std::cout << "Rectangle { Position: " << obj.position().toString()
            << ", Color: " << obj.color().toString()
            << ", Width: " << obj.width() 
            << ", Height: " << obj.height()
            << " }\n";
}

void Rectangle::render() const { printRectangle(*this); }

void Rectangle::render(SDL_Renderer *context) const {

  Point2D pts[5] = {position(), position() + Point2D(width(), 0.0f),
                    position() + Point2D(width(), height()),
                    position() + Point2D(0.0f, height()), position()};

  SDL_SetRenderDrawColor(context, color().r, color().g, color().b, color().a);
  for (int i = 0; i < 4; i++)
    SDL_RenderDrawLineF(context, pts[i].x, pts[i].y, pts[i + 1].x,
                        pts[i + 1].y);
}
