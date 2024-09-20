#include "scene.hpp"
#include <string>

void Scene::add_shape(std::unique_ptr<IShape> shape) {
  shapes.push_back(std::move(shape));
}

void Scene::apply(IOperation &op) {
  for (auto &shape : shapes) {
    shape->transform(op);
  }
}

std::string Scene::display() {
  std::string result = "Scene {\n";
  for (auto &shape : shapes) {
    result += "\t" + shape->display() + "\n";
  }
  result += "}";
  return result;
}
