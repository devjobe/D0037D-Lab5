#include <sstream>

#include "Rgba.h"

std::string Rgba::toString() const {
  std::stringstream ss;
  ss << "RGBA[" << int{r} << ", " << int{g} << ", " << int{b} << ", " << int{a}
     << "]";
  return ss.str();
}