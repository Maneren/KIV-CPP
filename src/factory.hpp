#pragma once
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

template <typename Interface> class Factory {
public:
  using MaybeUniquePtr = std::optional<std::unique_ptr<Interface>>;
  using ArgVector = std::vector<float>;
  using CreateFn = std::function<MaybeUniquePtr(const ArgVector &args)>;

  void register_type(const std::string &type, CreateFn fn) {
    creators[type] = fn;
  };
  MaybeUniquePtr create(const std::string &type, const ArgVector &args) {
    auto it = creators.find(type);
    return it != creators.end() ? it->second(args) : std::nullopt;
  };

private:
  std::map<std::string, CreateFn> creators;
};
