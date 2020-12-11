#include <iostream>

#include "Triangle.h"

static void printTriangle(Triangle const &obj) {
  std::cout << "Triangle { Position: " << obj.position().toString()
            << ", Color: " << obj.color().toString() << ", Base: " << obj.base()
            << ", Height: " << obj.height()
            << " }\n";
}

void Triangle::render() const { printTriangle(*this); }

void Triangle::render(SDL_Renderer *context) const {
  Point2D pts[4] = {position(), position() + Point2D(base()/2.0f, height()),
                    position() + Point2D(-base()/2.0f, height()), position()};

  SDL_SetRenderDrawColor(context, color().r, color().g, color().b, color().a);
  for (int i = 0; i < 3; i++)
    SDL_RenderDrawLineF(context, pts[i].x, pts[i].y, pts[i + 1].x,
                        pts[i + 1].y);
}