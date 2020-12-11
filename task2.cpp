#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include <chrono>
#include <deque>

#include <SDL2/SDL.h>

#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"


using namespace std::chrono_literals;

struct SizeI32 {
  int32_t width;
  int32_t height;
};

enum SHAPE_TYPES {
  SHAPE_RECTANGLE = 0,
  SHAPE_TRIANGLE = 1, 
  SHAPE_CIRCLE = 2,
  NUM_SHAPES = 3,
};

static SizeI32 randomSizeI32(std::default_random_engine &engine,
                             SizeI32 const &extent, SizeI32 const &margin) {
  auto x = std::uniform_int_distribution<int>(
      margin.width, extent.width - margin.width)(engine);
  auto y = std::uniform_int_distribution<int>(
      margin.height, extent.height - margin.height)(engine);
  return SizeI32{x, y};
}

static Rgba randomColor(std::default_random_engine &engine) {
  std::uniform_int_distribution<int> dist(0, 255);
  return Rgba{static_cast<unsigned char>(dist(engine)),
              static_cast<unsigned char>(dist(engine)),
              static_cast<unsigned char>(dist(engine)),
              static_cast<unsigned char>(dist(engine))};
}

static Point2D randomPoint(std::default_random_engine &engine,
                           SizeI32 const &extent, SizeI32 const &margin) {
  float x = std::uniform_real_distribution<float>(
      static_cast<float>(margin.width),
      static_cast<float>(extent.width - margin.width))(engine);
  float y = std::uniform_real_distribution<float>(
      static_cast<float>(margin.height),
      static_cast<float>(extent.height - margin.height))(engine);
  return Point2D(x, y);
}

static std::unique_ptr<Shape>
randomRectangle(std::default_random_engine &engine, SizeI32 const &extent) {

  auto size = randomSizeI32(engine, extent,
                            SizeI32{extent.width / 10, extent.height / 10});

  float x = std::uniform_real_distribution<float>(
      0, static_cast<float>(extent.width - size.width))(engine);
  float y = std::uniform_real_distribution<float>(
      0, static_cast<float>(extent.height - size.height))(engine);

  return std::make_unique<Rectangle>(Point2D(x, y), randomColor(engine),
                                     static_cast<float>(size.width),
                                     static_cast<float>(size.height));
}

static std::unique_ptr<Shape> randomTriangle(std::default_random_engine &engine,
                                             SizeI32 const &extent) {
  auto size = randomSizeI32(
      engine, extent, SizeI32{extent.width / 10 + 5, extent.height / 10 + 5});

  float x = std::uniform_real_distribution<float>(
      static_cast<float>(size.width / 2 + 5),
      static_cast<float>(extent.width - size.width / 2))(engine);
  float y = std::uniform_real_distribution<float>(
      5, static_cast<float>(extent.height - size.height - 5))(engine);

  return std::make_unique<Triangle>(Point2D(x, y), randomColor(engine),
                                    static_cast<float>(size.width),
                                    static_cast<float>(size.height));
}

static std::unique_ptr<Shape> randomCircle(std::default_random_engine &engine,
                                           SizeI32 const &extent) {

  int extent_max = std::min(extent.width, extent.height) - 10;
  auto radius = static_cast<float>(std::uniform_int_distribution<int>(
      extent_max / 20, extent_max / 20 * 9)(engine));

  float x = std::uniform_real_distribution<float>(
      radius + 5, extent.width - (radius + 5))(engine);
  float y = std::uniform_real_distribution<float>(
      radius + 5, extent.height - (radius + 5))(engine);

  return std::make_unique<Circle>(Point2D(x, y), randomColor(engine), radius);
}




using hr_clock = std::chrono::high_resolution_clock;

struct FrameTime {

  std::chrono::nanoseconds elapsed = {};
  hr_clock::time_point frameStart = hr_clock::now();

  void beginFrame() {
    auto now = hr_clock::now();
    elapsed = now - frameStart;
    frameStart = now;
  }
};

constexpr auto CREATION_WAIT_DURATION = 200ms;



class State {
  bool stopped_ = false;
  bool clearShapes_ = false;
  bool createRectangle_ = false;
  bool createTriangle_ = false;
  bool createCircle_ = false;
  hr_clock::duration creationWaitTimer_ = CREATION_WAIT_DURATION;
  std::vector<std::unique_ptr<Shape>> shapes_;

  SizeI32 renderedExtent_ = {};
  std::random_device randomDevice_;
  std::default_random_engine randomEngine_ =
      std::default_random_engine(randomDevice_());

public:
  bool const &is_stopped() { return stopped_; }

  void initialize(SDL_Renderer *context) {
    SDL_GetRendererOutputSize(context, &renderedExtent_.width,
                              &renderedExtent_.height);
  }

  void processInput(SDL_Event &event) {
    bool keydown = event.type == SDL_KEYDOWN;
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
    case SDLK_q:
      stopped_ = true;
      break;
    case SDLK_r:
      createRectangle_ = keydown;
      break;
    case SDLK_t:
      createTriangle_ = keydown;
      break;
    case SDLK_c:
      createCircle_ = keydown;
      break;
    case SDLK_x:

      clearShapes_ = !keydown;
      break;
    }
  }

  void processEvents() {

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        stopped_ = true;
        break;
      } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        processInput(event);
      } else if (event.type == SDL_WINDOW_INPUT_FOCUS) {
        createRectangle_ = false;
        createTriangle_ = false;
        createCircle_ = false;
      }
    }
  }

  void addShape(std::unique_ptr<Shape> shape) {
    shape->render();
    shapes_.push_back(std::move(shape));
    creationWaitTimer_ = 0ns;
  }

  void update(FrameTime const &timer) {
    if (clearShapes_) {
      shapes_.clear();
      clearShapes_ = false;
    }

    if (creationWaitTimer_ < CREATION_WAIT_DURATION) {
      creationWaitTimer_ += timer.elapsed;
    }

    if (creationWaitTimer_ >= CREATION_WAIT_DURATION) {
      if (createRectangle_) {
        addShape(randomRectangle(randomEngine_, renderedExtent_));
      }

      if (createTriangle_) {
        addShape(randomTriangle(randomEngine_, renderedExtent_));
      }

      if (createCircle_) {
        addShape(randomCircle(randomEngine_, renderedExtent_));
      }
    }
  }

  void render(SDL_Renderer *context) {
    SDL_SetRenderDrawColor(context, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(context);

    std::for_each(shapes_.cbegin(), shapes_.cend(),
                  [context](auto const &shape) { shape->render(context); });

    SDL_RenderPresent(context);
  }
};


int main() {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow("Shapes", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  State state = {};
  FrameTime timer = {};

  state.initialize(renderer);

  while (!state.is_stopped()) {
    timer.beginFrame();

    state.processEvents();
    state.update(timer);
    state.render(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
