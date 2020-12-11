#pragma once

#include "Shape.h"


class Triangle : public Shape {
public:
  Triangle(Point2D position, Rgba color, float base, float height)
      : Shape(position, color), base_(base), height_(height) {
    assert(base_ >= 0.0f && height_ >= 0.0f);
  };

  void render() const override;
  void render(SDL_Renderer *context) const override;

  float const &base() const { return base_; }
  void base(float value) {
    assert(value >= 0.0f);
    base_ = value;
  }

  float const &height() const { return height_; }
  void height(float value) {
    assert(value >= 0.0f);
    height_ = value;
  }

private:
  float base_;
  float height_;
};
