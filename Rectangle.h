#pragma once

#include "Shape.h"

class Rectangle : public Shape {
public:
  Rectangle(Point2D position, Rgba color, float width, float height)
      : Shape(position, color), width_(width), height_(height) {
    assert(width_ >= 0.0f && height_ >= 0.0f);
  };

  void render() const override;
  void render(SDL_Renderer *context) const override;

  float const &width() const { return width_; }
  void width(float value) {
    assert(value >= 0.0f);
    width_ = value;
  }

  float const &height() const { return height_; }
  void height(float value) {
    assert(value >= 0.0f);
    height_ = value;
  }

private:
  float width_;
  float height_;
};
