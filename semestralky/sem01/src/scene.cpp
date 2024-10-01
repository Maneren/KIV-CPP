#include "scene.hpp"
#include <string>

void Scene::add_shape(std::unique_ptr<IShape> shape) {
  shapes.push_back(std::move(shape));
}

void Scene::apply_transform(const IOperation &op) const {
  for (auto const &shape : shapes) {
    shape->transform(op);
  }
}

std::string Scene::display() const {
  std::string result = "Scene {\n";
  for (auto const &shape : shapes) {
    result += "\t" + shape->display() + "\n";
  }
  result += "}";
  return result;
}
