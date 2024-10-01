#include "translate.hpp"

Point Translate::operator()(const Point point) const { return point + delta; }
