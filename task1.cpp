
#include <iostream>
#include <algorithm>

using namespace std;

#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"


void testRendering(Shape const *const *shapes, int count) {
  for_each(shapes, shapes + count, [](auto shape) { shape->render(); });
  cout << endl;
}

int main() {
  Shape *shapes[3] = {
      new Rectangle(Point2D(10.0f, 20.0f), Rgba{10, 20, 30, 40}, 50.0f, 100.0f),
      new Triangle(Point2D(40.0f, -40.0f), Rgba{250, 200, 130, 40}, 125.0f,
                   75.0f),
      new Circle(Point2D(-10.0f, -20.0f), Rgba{140, 0, 100, 255}, 25.0f),
  };

  testRendering(shapes, 3);

  return 0;
}
