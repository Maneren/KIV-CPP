#include "translate.hpp"

Point Translate::transform(const Point point) const { return point + delta; }
