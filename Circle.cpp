#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

#include "Circle.h"

static void printCircle(Circle const &obj) {
  std::cout << "Circle { Position: " << obj.position().toString()
            << ", Color: " << obj.color().toString()
            << ", Radius: " << obj.radius() << " }\n";
}

void Circle::render() const { printCircle(*this); }

constexpr int CIRCLE_SEGMENTS = 100;
constexpr float CIRCLE_SEGMENT_ANGLE = static_cast<float>(M_PI * 2 / CIRCLE_SEGMENTS);

void Circle::render(SDL_Renderer *context) const {
  SDL_SetRenderDrawColor(context, color().r, color().g, color().b, color().a);
  auto pt0 = position() + Point2D(radius(), 0.0f);
  for (int i = 1; i < CIRCLE_SEGMENTS; i++) {

    auto pt1 = position() + Point2D(radius() * cosf(CIRCLE_SEGMENT_ANGLE * i),
                                    radius() * sinf(CIRCLE_SEGMENT_ANGLE * i));
    SDL_RenderDrawLineF(context, pt0.x, pt0.y, pt1.x, pt1.y);

    pt0 = pt1;
  }

  {
    auto pt1 = position() + Point2D(radius(), 0.0f);
    SDL_RenderDrawLineF(context, pt0.x, pt0.y, pt1.x, pt1.y);
  }
}