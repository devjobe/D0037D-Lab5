
#include "Shape.h"

class Circle : public Shape {
public:
  Circle(Point2D position, Rgba color, float radius)
      : Shape(position, color), radius_(radius) {
    assert(radius_ >= 0.0f);
  };

  void render() const override;
  void render(SDL_Renderer *context) const override;

  float const &radius() const { return radius_; }
  void radius(float value) {
    assert(value >= 0.0f);
    radius_ = value;
  }

private:
  float radius_;
};
