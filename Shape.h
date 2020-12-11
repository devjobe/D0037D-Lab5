#pragma once

#include <assert.h>

#include "SDL2/SDL.h"

#include "Point2D.h"
#include "Rgba.h"



class Shape {
public:
  Shape(Point2D position, Rgba color) : position_(position), color_(color) {}

  virtual ~Shape();
  virtual void render() const = 0;
  virtual void render(SDL_Renderer *context) const = 0;

  Point2D const &position() const { return position_; }
  void position(Point2D pos) { position_ = pos; }

  Rgba const &color() const { return color_; }
  void color(Rgba rgba) { color_ = rgba; }

private:
  Point2D position_;
  Rgba color_;
};



